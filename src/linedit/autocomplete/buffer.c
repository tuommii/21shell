/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:08:40 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/10 08:54:14 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// returns string until to cursor, discards spaces
char *get_word_at(char buffer[INPUT_BUFFER], int cursor)
{
	int x = cursor;
	int len = ft_strlen(buffer);
	char *res;

	// input is empty
	if (!x && buffer[x] == '\0')
	{
		return ft_strdup("");
	}

	// cursor is top of first char
	if (x && !ft_isspace(buffer[x]) && ft_isspace(buffer[x - 1]))
	{
		return ft_strdup(" ");
	}

	// cursor is at end of string
	if (x == len)
	{
		x--;
		while (x > 0 && !ft_isspace(buffer[x]))
			x--;
	}

	// cursor is middle of something

	// cursor is top of space
	else if (ft_isspace(buffer[x]))
	{
		if (x)
			x--;
		if (ft_isspace(buffer[x]))
		{
			return ft_strdup(" ");
		}
		while (x > 0 && !ft_isspace(buffer[x]))
		{
			x--;
		}
	}

	// cursor is top of string
	else if (!ft_isspace(buffer[x]))
	{
		while (x > 0 && !ft_isspace(buffer[x]))
			x--;
	}

	if (x || ft_isspace(buffer[x]))
		x++;
	int size = cursor - x;
	res = malloc(sizeof(char) * size + 1);
	ft_strncpy(res, buffer + x, size);
	res[size] = '\0';
	return res;
}

void	delete_word(t_line *line, char *word)
{
	int len = ft_strlen(word);

	// If cursor is in the middle of word
	while (line->input[line->pos] != ' ')
	{
		if (line->input[line->pos] == '\0')
			break;
		line->pos++;
		len++;
	}

	// Do not remove strating $
	if (line->input[line->pos - len] == '$')
	{
		len--;
	}

	while (len)
	{
		ft_insert(line->input, line->pos, 0);
		line->pos--;
		line->len--;
		len--;
	}
}

void	insert_word(t_line *line, char *word)
{
	while (*word)
	{
		apped_or_insert(line, *word);
		word++;
	}
}
