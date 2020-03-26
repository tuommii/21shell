/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 19:15:37 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/26 13:20:22 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void print_prompt(t_line *line)
{
	// ft_printf(FT_GREEN);
	ft_printf("%-*s", line->prompt_len, line->prompt);
	// ft_printf(FT_RESET);
}

static void check_newline(t_line *line, int *rows)
{
	if (line->pos && line->pos == line->len && (line->pos + line->prompt_len) % line->cols == 0)
	{
		ft_printf("\n");
		ft_printf("\r");
		(*rows)++;
		if (*rows > line->lines_used)
			line->lines_used = *rows;
	}
}

void redraw_input(t_line *line)
{
	int rows;
	int pos;
	int col;

	rows = (line->prompt_len + line->len + line->cols - 1) / line->cols;
	clear_rows(line);
	print_prompt(line);
	ft_printf("%-*s", line->len, line->input);
	check_newline(line, &rows);
	pos = (line->prompt_len + line->pos + line->cols) / line->cols;
    if (rows-pos > 0) {
        ft_printf("\x1b[%dA", rows-pos);
    }
	col = (line->prompt_len+line->pos) % line->cols;
	if (col)
		ft_printf("\r\x1b[%dC", col);
	else
		ft_printf("\r");
	line->old_pos = line->pos;
}
