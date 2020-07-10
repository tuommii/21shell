/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:08:40 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/10 13:47:49 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static void	goto_word_begin(char buffer[INPUT_BUFFER], int *x)
{
	while (*x > 0 && !ft_isspace(buffer[*x]))
		(*x)--;
}

static char	*checks(char buffer[INPUT_BUFFER], int x, int len)
{
	if (!x && buffer[x] == '\0')
		return (ft_strdup(""));
	if (x && !ft_isspace(buffer[x]) && ft_isspace(buffer[x - 1]))
		return (ft_strdup(" "));
	return (NULL);
}

static char	*allocate(char buffer[INPUT_BUFFER], int cursor, int x)
{
	char	*str;
	int		size;

	size = cursor - x;
	str = malloc(sizeof(char) * size + 1);
	ft_strncpy(str, buffer + x, size);
	str[size] = '\0';
	return (str);
}

/*
** Returns string until to cursor, discards spaces
*/

char		*get_word_at(char buffer[INPUT_BUFFER], int cursor)
{
	int		x;
	int		len;
	char	*res;

	len = ft_strlen(buffer);
	x = cursor;
	if ((res = checks(buffer, x, len)) != NULL)
		return (res);
	if (x-- == len)
		goto_word_begin(buffer, &x);
	else if (ft_isspace(buffer[x]))
	{
		if (x)
			x--;
		if (ft_isspace(buffer[x]))
			return (ft_strdup(" "));
		goto_word_begin(buffer, &x);
	}
	else if (!ft_isspace(buffer[x]))
		goto_word_begin(buffer, &x);
	if (x || ft_isspace(buffer[x]))
		x++;
	return (allocate(buffer, cursor, x));
}

void		delete_word(t_line *line, char *word)
{
	int len;

	len = ft_strlen(word);
	while (line->input[line->pos] != ' ')
	{
		if (line->input[line->pos] == '\0')
			break ;
		line->pos++;
		len++;
	}
	if (line->input[line->pos - len] == '$')
		len--;
	while (len)
	{
		ft_insert(line->input, line->pos, 0);
		line->pos--;
		line->len--;
		len--;
	}
}
