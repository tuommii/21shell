/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 09:05:01 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/13 09:49:06 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

int	calc_rows_used(t_line *line)
{
	return ((line->prompt_len + line->len + line->cols - 1) / line->cols);
}

int	calc_row_pos(t_line *line)
{
	return ((line->prompt_len + line->old_pos + line->cols) / line->cols);
}
