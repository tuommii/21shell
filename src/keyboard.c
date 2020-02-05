/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:16:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/05 12:18:03 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	return (code);
}

// TODO: Multiline support
int handle_printable(t_shell *sh)
{
	if (ft_isprint(sh->key))
	{
		if (sh->x - sh->prompt_len < sh->len)
		{
			ft_insert(sh->input, sh->x - sh->prompt_len + 1, (char)sh->key);
		}
		else if (sh->x - sh->prompt_len == sh->len)
		{
			sh->input[sh->i] = (char)sh->key;
		}
		sh->len++;
		move_right(sh);
		return (1);
	}
	return (0);
}

int handle_arrow_keys(t_shell *sh)
{
	if (sh->key == LEFT)
		move_left(sh);
	else if (sh->key == RIGHT)
		move_right(sh);
	else if (sh->key == UP)
	{
		// If no history, delete line. just placeholder action
		if (sh->hist && sh->hist->prev && sh->hist_i < sh->hist_count)
		{
			erase_input(sh);
			t_hist *node = hist_pop(&sh->hist, sh->hist_i);
			ft_strcpy(sh->input, node->str);
			sh->len = ft_strlen(sh->input);
			CURSOR_RIGHT(sh->prompt_len + sh->len - sh->x);
			sh->x = sh->prompt_len + sh->len;
			sh->i = sh->len;
			sh->hist_i++;
		}
	}
	else if (sh->key == DOWN)
	{
		if (sh->hist_i == 1)
		{
			sh->hist_i--;
			erase_input(sh);
		}
		if (sh->hist_i > 1)
		{
			sh->hist_i--;
			erase_input(sh);
			t_hist *node = hist_pop(&sh->hist, sh->hist_i-1);
			ft_strcpy(sh->input, node->str);
			sh->len = ft_strlen(sh->input);
			CURSOR_RIGHT(sh->prompt_len + sh->len - sh->x);
			sh->x = sh->prompt_len + sh->len;
			sh->i = sh->len;
		}
	}
	if (sh->key == LEFT || sh->key == RIGHT || sh->key == UP)
		return (1);
	return (0);
}

int handle_command_keys(t_shell *sh)
{
	if (sh->key == TAB)
	{
		tputs(tgetstr("vb", NULL), 1, print_char);
		return (1);
	}
	else if (sh->key == BACKSPACE)
	{
		ft_insert(sh->input, sh->i, 0);
		move_left(sh);
		print_input(sh);
		if (sh->len > 0)
			sh->len--;
		return (1);
	}
	else if (sh->key == ESC)
	{
		ft_printf("\n");
		return (ESC);
	}
	return (0);
}

int handle_nav_keys(t_shell *sh)
{
	if (sh->key == HOME_KEY)
	{
		start_of_input(sh);
		return (1);
	}
	else if (sh->key == END_KEY)
	{
		end_of_input(sh);
		return (1);
	}
	else if (sh->key == CTRL_LEFT)
	{
		return (1);
	}
	else if (sh->key == CTRL_D)
	{
		if (sh->len && (sh->x - sh->prompt_len) < sh->len)
		{
			ft_insert(sh->input, sh->i+1, 0);
			// move_left(sh);
			print_input(sh);
			if (sh->len > 0)
				sh->len--;
			return (1);
		}
		else if (!sh->len)
		{
			// TODO: Global exit func
			cleanup(sh);
		}

	}
	return (0);
}

// TODO: Ctrl+D deletes selected char
int which_key(t_shell *sh)
{
	if (sh->key != UP && sh->key != DOWN)
	{
		sh->hist_i = 0;
	}
	if (handle_printable(sh))
	{

	}
	else if (handle_arrow_keys(sh))
		;
	else if (handle_command_keys(sh) == ESC)
		return (ESC);
	else if (handle_nav_keys(sh) == ESC)
		;
	else if (sh->key == CTRL_L)
	{
		tputs(tgetstr("cl", NULL), 1, print_char);
		sh->y = 0;
		sh->x = sh->prompt_len;
		return (CTRL_L) ;
	}
	return (0);
}
