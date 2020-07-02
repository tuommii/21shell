/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:27:19 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/02 20:11:08 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

int	check_arrow_keys(t_line *line)
{
	if (line->key == LEFT)
	{
		handle_left_key(line);
		return (1);
	}
	else if (line->key == RIGHT)
	{
		handle_right_key(line);
		return (1);
	}
	else if (line->key == UP)
	{
		hist_next(line);
		return (1);
	}
	else if (line->key == DOWN)
	{
		hist_prev(line);
		return (1);
	}
	return (0);
}

int	check_command_keys(t_line *line)
{
	if (line->key == TAB)
	{
		tputs(tgetstr("vb", NULL), 1, &print_char);
		return (1);
	}
	else if (line->key == BACKSPACE)
	{
		handle_backspace(line);
		return (1);
	}
	return (0);
}

int	check_ctrl_arrow_keys(t_line *line)
{
	if (line->key == CTRL_LEFT)
	{
		goto_prev_word(line);
		return (1);
	}
	else if (line->key == CTRL_RIGHT)
	{
		goto_next_word(line);
		return (1);
	}
	else if (line->key == CTRL_UP)
	{
		goto_row_up(line);
		return (1);
	}
	else if (line->key == CTRL_DOWN)
	{
		goto_row_down(line);
		return (1);
	}
	return (0);
}

int	check_copy_paste_del(t_line *line)
{
	if (line->key == DELETE || (line->key == CTRL_D && line->len))
	{
		handle_delete(line);
		return (1);
	}
	else if (line->key == CTRL_P)
	{
		if (!line->is_cut)
			clipboard_update(&line->clipboard);
		line->is_cut = 0;
		clipboard_draw(line);
		ft_bzero(line->clipboard.content, INPUT_BUFFER);
		return (1);
	}
	else if (line->key == CTRL_X)
	{
		ft_strcpy(&line->clipboard.content, line->input);
		line->is_cut = 1;
		ft_bzero(line->input, INPUT_BUFFER);
		line->pos = 0;
		line->len = 0;
		redraw_input(line);
		return (1);
	}
	else if (line->key == CTRL_W)
	{
		int len = line->pos;
		if (!len)
			return ;
		ft_memcpy(line->internal, line->input, len);
		while (len-- > 0)
		{
			ft_insert(line->input, 1, 0);
			line->len--;
		}
		line->pos = 0;
		redraw_input(line);
	}
	else if (line->key == CTRL_Y)
	{
		int len = ft_strlen(line->internal);
		if (!len || (line->len + len) > INPUT_BUFFER)
			return ;
		if (line->pos != line->len)
		{
			int i = -1;
			while (++i < len)
				ft_insert(line->input, line->pos + i + 1, line->internal[i]);
		}
		else
			ft_strcpy(line->input + line->len, line->internal);
		line->len += len;
		line->pos += len;
		redraw_input(line);
	}
	return (0);
}

int	check_terminating_keys(t_line *line)
{
	if (line->key == ESC || (line->key == CTRL_D && !line->len))
	{
		toggle_raw(1, 0);
		return (1);
	}
	return (0);
}
