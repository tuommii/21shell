/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suggestions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:35:58 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/27 20:59:59 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void linedit_completion_cb(t_line *line, autocomp_cb *cb) {
	line->cb = cb;
}

void hello(const char *s, t_suggestions *arr)
{
	if (arr)
	{

	}

	ft_printf("%s", s);
}
