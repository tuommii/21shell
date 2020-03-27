/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:07:21 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/27 19:03:35 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static void	text_to_clipboard(t_line *line, int start, int end)
{
	int len;

	len = end - start;
	ft_strncpy(line->clipboard.content, line->input + start, len);
	line->clipboard.content[len] = '\0';
}

static void	cut_from_clipboard(t_line *line, int start, int end)
{
	int len;

	len = end - start;
	while (len-- > 0)
	{
		ft_insert(line->input, start + 1, 0);
		line->len--;
	}
}

static int	reset_state(t_line *line, int *state, int *start)
{
	if (line->pos <= *start)
	{
		*start = 0;
		*state = 0;
		return (1);
	}
	return (0);
}

/*
** First key combo sets start index and second sets end
** state holds if is pressed already and start position for that press
** Returns 1 when cut is done and text is available in line->clipboard
*/
int			copy_cat(t_line *line, int is_cut, int *state, int *start)
{
	if (!*state)
	{
		*start = line->pos;
		*state = 1;
		tputs(tgetstr("vb", NULL), 1, &print_char);
		return (0);
	}
	if (reset_state(line, state, start))
		return (0);
	text_to_clipboard(line, *start, line->pos);
	*state = 0;
	if (!is_cut)
	{
		tputs(tgetstr("vb", NULL), 1, &print_char);
		tputs(tgetstr("vb", NULL), 1, &print_char);
	}
	else
	{
		cut_from_clipboard(line, *start, line->pos);
		line->pos -= line->pos - *start;
		line->clipboard.is_cut = 1;
	}
	redraw_input(line);
	return (1);
}

void		paste(t_line *line)
{
	int len;
	int i;

	len = ft_strlen(line->clipboard.content);
	if (!len || line->len + ft_strlen(line->clipboard.content) >= INPUT_BUFFER)
		return ;
	if (line->pos != line->len)
	{
		i = -1;
		while (++i < len)
			ft_insert(line->input, line->pos + i + 1, line->clipboard.content[i]);
	}
	else
		ft_strcpy(line->input + line->len, line->clipboard.content);
	line->len += len;
	line->pos += len;
	if (line->clipboard.is_cut)
	{
		ft_bzero(line->clipboard.content, INPUT_BUFFER);
		line->clipboard.is_cut = 0;
	}
	redraw_input(line);
}
