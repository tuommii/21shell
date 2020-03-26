/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:42:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/26 11:10:32 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void goto_row_down(t_line *line)
{
	int rows = (line->len + line->cols - 1) / line->cols;
	int rpos = (line->old_pos + line->cols) / line->cols;
	if (line->lines_used > 1 && rpos < rows)
	{
		if ((line->pos + line->cols) > line->len)
		{
			goto_end(line);
		}
		else
		{
			line->pos += line->cols;
			redraw_input(line);
		}
	}
}

void goto_row_up(t_line *line)
{
	int rpos = (line->old_pos + line->cols) / line->cols;

	if (line->lines_used > 1 && rpos > 1)
	{
		line->pos -= line->cols;
		redraw_input(line);
	}
}

/*
** After enter is pressed place cursor row below output
*/

void reposition(t_line *line)
{
	ft_printf("\r");
	ft_printf("\n");
	erase_input(line);
}

void clear_rows(t_line *line)
{
	int plen = line->prompt_len;
	int rows = (plen + line->len + line->cols - 1) / line->cols;
	int rpos = (plen + line->old_pos + line->cols) / line->cols;
	int old_rows = line->lines_used;

	if (rows > line->lines_used)
	{
		line->lines_used = rows;
	}
	if (old_rows-rpos > 0)
	{
		ft_printf("\x1b[%dB", old_rows - rpos);
	}

	for (int j = 0; j < old_rows - 1; j++)
	{
		ft_printf("\r\x1b[0K\x1b[1A");
	}
    ft_printf("\r\x1b[0K");
}
