/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:40:03 by mtuomine          #+#    #+#             */
/*   Updated: 2020/06/22 10:47:31 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void	goto_end(t_line *line)
{
	if (line->pos != line->len)
	{
		line->pos = line->len;
		redraw_input(line);
	}
}

void	goto_begin(t_line *line)
{
	if (line->pos != 0)
	{
		line->pos = 0;
		redraw_input(line);
	}
}

void	goto_prev_word(t_line *line)
{
	if (line->len > 0 && line->pos > 0)
	{
		line->pos--;
		while (line->input[line->pos] == ' ' && line->pos > 0)
		{
			line->pos--;
		}
		while (line->pos - 1 >= 0 && line->input[line->pos - 1] != ' ')
		{
			line->pos--;
		}
		redraw_input(line);
	}
}

void	goto_next_word(t_line *line)
{
	while (line->pos < line->len && line->input[line->pos] == ' ')
	{
		line->pos++;
	}
	while (line->pos < line->len && line->input[line->pos] != ' ')
	{
		line->pos++;
	}
	while (line->pos < line->len && line->input[line->pos] == ' ')
	{
		line->pos++;
	}
	redraw_input(line);
}
