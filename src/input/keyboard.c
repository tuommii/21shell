/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:16:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 16:09:17 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_insert(char *str, int pos, char c)
{
	int i;
	int len;

	len = ft_strlen(str) - 1;
	if (!str || pos < 1 || pos > len + 1)
		return ;
	if (!c)
	{
		i = pos - 1;
		while (i < len)
		{
			str[i] = str[i + 1];
			i++;
		}
		str[len] = '\0';
		return ;
	}
	i = len;
	while (i >= pos - 1)
	{
		str[i + 1] = str[i];
		i--;
	}
	str[pos - 1] = c;
}

int	keypress(void)
{
	int		i;
	int		code;
	char	seq[KEYBOARD_BUFFER + 1];

	ft_bzero(seq, KEYBOARD_BUFFER);
	read(STDIN_FILENO, &seq, KEYBOARD_BUFFER);
	seq[KEYBOARD_BUFFER] = '\0';
	i = 0;
	code = 0;
	while (seq[i])
	{
		code += seq[i];
		i++;
	}
	// if (!(ft_strcmp(seq, "[1;5D") == 0))
	// 	ft_printf("%s", seq);
	// else
	// 	ft_printf("CTRL+LEFT", seq);
	return (code);
}

// TODO: Multiline support
int handle_printable(void)
{
	if (ft_isprint(g_sh.key))
	{
		if (g_sh.x - g_sh.prompt_len < g_sh.len)
		{
			ft_insert(g_sh.input, g_sh.x - g_sh.prompt_len + 1, (char)g_sh.key);
		}
		else if (g_sh.x - g_sh.prompt_len == g_sh.len)
		{
			g_sh.input[g_sh.i] = (char)g_sh.key;
		}
		g_sh.len++;
		move_right();
		return (1);
	}
	return (0);
}

int handle_arrow_keys(void)
{
	if (g_sh.key == LEFT)
		move_left();
	else if (g_sh.key == RIGHT)
		move_right();
	else if (g_sh.key == UP)
	{
		// If no history, delete line. just placeholder action
		if (g_sh.hist && g_sh.hist->prev && g_sh.hist_i < g_sh.hist_count)
		{
			erase_input();
			t_hist *node = hist_pop(&g_sh.hist, g_sh.hist_i);
			ft_strcpy(g_sh.input, node->str);
			g_sh.len = ft_strlen(g_sh.input);
			CURSOR_RIGHT(g_sh.prompt_len + g_sh.len - g_sh.x);
			g_sh.x = g_sh.prompt_len + g_sh.len;
			g_sh.i = g_sh.len;
			g_sh.hist_i++;
		}
	}
	else if (g_sh.key == DOWN)
	{
		if (g_sh.hist_i == 1)
		{
			g_sh.hist_i--;
			erase_input();
		}
		if (g_sh.hist_i > 1)
		{
			g_sh.hist_i--;
			erase_input();
			t_hist *node = hist_pop(&g_sh.hist, g_sh.hist_i-1);
			ft_strcpy(g_sh.input, node->str);
			g_sh.len = ft_strlen(g_sh.input);
			CURSOR_RIGHT(g_sh.prompt_len + g_sh.len - g_sh.x);
			g_sh.x = g_sh.prompt_len + g_sh.len;
			g_sh.i = g_sh.len;
			// g_sh.hist_i++;
		}
		// If started rolling history
		// change
		// if no next
		// empty input
	}
	if (g_sh.key == LEFT || g_sh.key == RIGHT || g_sh.key == UP)
		return (1);
	return (0);
}

int handle_command_keys(void)
{
	if (g_sh.key == TAB)
	{
		tputs(tgetstr("vb", NULL), 1, print_char);
		return (1);
	}
	else if (g_sh.key == BACKSPACE)
	{
		ft_insert(g_sh.input, g_sh.i, 0);
		move_left();
		print_input();
		if (g_sh.len > 0)
			g_sh.len--;
		return (1);
	}
	else if (g_sh.key == ESC)
	{
		ft_printf("\n");
		return (ESC);
	}
	return (0);
}

int handle_nav_keys(void)
{
	if (g_sh.key == HOME_KEY)
	{
		start_of_input();
		return (1);
	}
	else if (g_sh.key == END_KEY)
	{
		end_of_input();
		return (1);
	}
	else if (g_sh.key == CTRL_LEFT)
	{
		return (1);
	}
	else if (g_sh.key == CTRL_D)
	{
		if (g_sh.len && (g_sh.x - g_sh.prompt_len) < g_sh.len)
		{
			ft_insert(g_sh.input, g_sh.i+1, 0);
			// move_left(sh);
			print_input();
			if (g_sh.len > 0)
				g_sh.len--;
			return (1);
		}
		else if (!g_sh.len)
		{
			// TODO: Global exit func
			cleanup();
		}

	}
	return (0);
}

// TODO: Ctrl+D deletes selected char
int which_key(void)
{
	if (g_sh.key != UP && g_sh.key != DOWN)
	{
		g_sh.hist_i = 0;
	}
	if (handle_printable())
	{

	}
	else if (handle_arrow_keys())
		;
	else if (handle_command_keys() == ESC)
		return (ESC);
	else if (handle_nav_keys() == ESC)
		;
	else if (g_sh.key == CTRL_L)
	{
		tputs(tgetstr("cl", NULL), 1, print_char);
		g_sh.y = 0;
		g_sh.x = g_sh.prompt_len;
		return (CTRL_L) ;
	}
	return (0);
}
