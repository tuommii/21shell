/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 10:41:49 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/02 10:49:38 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void		hist_next(t_line *line)
{
	t_hist *node;

	if (line->hist && line->hist->prev && line->hist_i < line->hist_count)
	{
		clear_rows(line);
		erase_input(line);
		node = hist_pop(&line->hist, line->hist_i);
		ft_strcpy(line->input, node->str);
		line->len = ft_strlen(line->input);
		goto_end(line);
		line->hist_i++;
	}
}

void		hist_prev(t_line *line)
{
	t_hist *node;

	if (line->hist_i == 1)
	{
		clear_rows(line);
		erase_input(line);
		line->hist_i--;
		line->pos = 0;
		redraw_input(line);
	}
	else if (line->hist_i > 1)
	{
		line->hist_i--;
		clear_rows(line);
		erase_input(line);
		node = hist_pop(&line->hist, line->hist_i - 1);
		ft_strcpy(line->input, node->str);
		line->len = ft_strlen(line->input);
		line->pos = line->len;
		redraw_input(line);
	}
}
