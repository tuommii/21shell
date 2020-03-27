/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:27:19 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/27 15:06:37 by mtuomine         ###   ########.fr       */
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
	if (line->key == ENTER)
	{
		if (*line->input)
		{
			line->hist_count += hist_append(&line->hist, line->input);
			if (line->hist_count > MAX_HISTORY)
				line->hist_count = MAX_HISTORY;
		}
		line->hist_i = 0;
		ft_strcpy(line->debug, line->input);
		reposition(line);
		return (1);
	}
	else if (line->key == TAB)
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
		paste(line);
		return (1);
	}
	else if (line->key == CTRL_X)
	{
		copy_cat(line, 1, &line->cut_running, &line->cut_start);
		return (1);
	}
	else if (line->key == CTRL_K)
	{
		copy_cat(line, 0, &line->copy_running, &line->copy_start);
		return (1);
	}
	return (0);
}

int	check_terminating_keys(t_line *line)
{
	if (line->key == ESC || (line->key == CTRL_D && !line->len))
	{
		linedit_config(1);
		return (1);
	}
	return (0);
}
