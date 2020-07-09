/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 19:15:37 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/09 19:33:07 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static void	check_newline(t_line *line, int *rows)
{
	if (line->pos && line->pos == \
	line->len && (line->pos + line->prompt_len) % line->cols == 0)
	{
		ft_putstr("\n\r");
		(*rows)++;
		if (*rows > line->lines_used)
			line->lines_used = *rows;
	}
}

static void	move_up(int rows, int pos)
{
	char *tmp;

	tmp = ft_itoa(rows - pos);
	ft_putstr("\x1b[");
	ft_putstr(tmp);
	ft_putstr("A");
	free(tmp);
}

static void	move_right(int col)
{
	char *tmp;

	tmp = ft_itoa(col);
	ft_putstr("\r\x1b[");
	ft_putstr(tmp);
	ft_putstr("C");
	free(tmp);
}

void		redraw_input(t_line *line)
{
	int		rows;
	int		pos;
	int		col;
	char	*tmp;

	rows = (line->prompt_len + line->len + line->cols - 1) / line->cols;
	clear_rows(line);
	print_prompt(line);
	ft_putstr(line->input);
	check_newline(line, &rows);
	pos = (line->prompt_len + line->pos + line->cols) / line->cols;
	if (rows - pos > 0)
		move_up(rows, pos);
	col = (line->prompt_len + line->pos) % line->cols;
	if (col)
		move_right(col);
	else
		ft_putstr("\r");
	line->old_pos = line->pos;
}
