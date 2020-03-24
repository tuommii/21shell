/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 20:01:01 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/09 07:39:25 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

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

int handle_right_key(t_line *line)
{
	if (line->pos != line->len)
	{
		line->pos++;
		redraw_input(line);
	}
	return (1);
}

int handle_left_key(t_line *line)
{
	if (line->pos > 0)
	{
		line->pos--;
		redraw_input(line);
	}
	return (1);
}

// Delete char left of cursor and move cursor
int handle_backspace(t_line *line)
{
	if (line->pos > 0 && line->len > 0)
	{
		ft_insert(line->input, line->pos, 0);
		line->len--;
		line->pos--;
		redraw_input(line);
	}
	return (1);
}

// Delete char on cursor and stay still
int handle_delete(t_line *line)
{
	if (line->len > 0 && line->pos < line->len)
	{
		ft_insert(line->input, line->pos + 1, 0);
		line->len--;
		redraw_input(line);
	}
	return (1);
}
