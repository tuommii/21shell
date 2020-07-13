/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:42:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/13 09:10:04 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

int		goto_row_down(t_line *line)
{
	int rows;
	int rpos;

	rows = (line->len + line->cols) / line->cols;
	rpos = (line->old_pos + line->cols) / line->cols;
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
	return (1);
}

int		goto_row_up(t_line *line)
{
	int rpos;

	rpos = (line->old_pos + line->cols) / line->cols;
	if (line->lines_used > 1 && rpos > 1)
	{
		line->pos -= line->cols;
		redraw_input(line);
	}
	return (1);
}

/*
** After enter is pressed place cursor row below output
*/

void	reposition(t_line *line)
{
	ft_putstr("\r\n");
	erase_input(line);
}

void	clear_rows(t_line *line)
{
	int rows;
	int rpos;
	int old_rows;
	int j;

	rows = calc_rows_used(line);
	rpos = calc_row_pos(line);
	old_rows = line->lines_used;
	if (rows > line->lines_used)
		line->lines_used = rows;
	if (old_rows - rpos > 0)
	{
		ft_putstr("\x1b[");
		ft_putnbr(old_rows - rpos);
		ft_putchar('B');
	}
	j = 0;
	while (j < (old_rows - 1))
	{
		ft_putstr("\r\x1b[0K\x1b[1A");
		j++;
	}
	ft_putstr("\r\x1b[0K");
}
