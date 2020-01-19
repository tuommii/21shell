/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:16:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/19 06:28:58 by mtuomine         ###   ########.fr       */
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
		ft_bzero(sh->input, INPUT_BUFFER);
		end_of_input(sh);
		start_of_input(sh);
		// if (sh->i < sh->len)
		// {
		// 	CURSOR_RIGHT(sh->len - sh->i);
		// 	sh->x += sh->len - sh->i;
		// 	sh->i = sh->len;
		// }
		// if (sh->len)
		// 	CURSOR_LEFT(sh->len);
		// sh->i -= sh->len;
		// sh->x -= sh->len;
		// sh->len = 0;
		// if (sh->len)
		ft_printf("\033[K");
	}
	// else if (sh->key == UP)
	// {
	// 	ft_printf(tgetstr("ce", NULL));
	// 	if (sh->hist && sh->hist->prev)
	// 	{
	// 		ft_bzero(sh->input, INPUT_BUFFER);
	// 		sh->len = 0;
	// 		return (1);
	// 		// print_input(sh);
	// 		// ft_strcpy(sh->input, sh->hist->prev->str);
	// 		// sh->len = ft_strlen(sh->input);
	// 		// // TODO: handle case if input is longer than history
	// 		// while (sh->x < sh->prompt_len + sh->len)
	// 		// {
	// 		// 	// ft_printf("\033[<%d>", 5);
	// 		// 	move_right(sh);
	// 		// }
	// 	}
	// }
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

int which_key(t_shell *sh)
{
	if (handle_printable(sh))
		;
	else if (handle_arrow_keys(sh))
		;
	else if (handle_command_keys(sh) == ESC)
		return (ESC);
	else if (sh->key == CTRL_L)
	{
		tputs(tgetstr("cl", NULL), 1, print_char);
		sh->y = 0;
		sh->x = sh->prompt_len;
		return (CTRL_L) ;
	}
	return (0);
}
