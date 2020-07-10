/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 13:59:00 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/10 21:13:54 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

int	cut_to_start(t_line *line)
{
	int len;

	len = line->pos;
	if (!len)
		return (1);
	ft_bzero(line->internal, INPUT_BUFFER);
	ft_memcpy(line->internal, line->input, len);
	while (len-- > 0)
	{
		ft_insert(line->input, 1, 0);
		line->len--;
	}
	line->pos = 0;
	redraw_input(line);
	return (1);
}

int	cut_to_end(t_line *line)
{
	int len;

	len = line->len - line->pos;
	if (!len)
		return (1);
	ft_bzero(line->internal, INPUT_BUFFER);
	ft_strncpy(line->internal, line->input + line->pos, len);
	while (line->len > line->pos)
	{
		ft_insert(line->input, line->len, 0);
		line->len--;
	}
	redraw_input(line);
	return (1);
}

int	yank(t_line *line)
{
	int len;
	int i;

	len = ft_strlen(line->internal);
	if (!len || (line->len + len) > INPUT_BUFFER)
		return (1);
	if (line->pos != line->len)
	{
		i = -1;
		while (++i < len)
			ft_insert(line->input, line->pos + i + 1, line->internal[i]);
	}
	else
		ft_strcpy(line->input + line->len, line->internal);
	line->len += len;
	line->pos += len;
	redraw_input(line);
	return (1);
}
