/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:14:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 08:39:49 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// decide context
char *get_context(char buffer[INPUT_BUFFER], int cursor)
{
	char *word;
	char *ctx;

	if (!(word = get_word_at(buffer, cursor)))
	{
		free(word);
		return (NULL);
	}

	if (word[0] == '\0' || (ft_strlen(word) - cursor) <= 0)
	{
		ctx = ft_strdup(CTX_EXEC);
	}

	else if (word[0] == '$')
	{
		ctx = ft_strdup(CTX_ENV);
	}

	else if (word[0] == '-')
	{
		ctx = ft_strdup(CTX_FLAG);
	}

	else if (!cursor && buffer[cursor] == ' ')
	{
		ctx = ft_strdup(CTX_EXEC);
	}

	// TODO: recursive with ' '
	// else if (word[0] == '/' || word[0] == '.' || word[0] == ' ')
	else
	{
		ctx = ft_strdup(CTX_PATH);
	}
	free(word);
	return (ctx);
}

// copy suitable suggestions only
void filter(t_completions *comps)
{
	if (!comps->word)
		return ;

	char *cpy = comps->word;
	if (cpy[0] == '$' && cpy[1])
	{
		cpy++;
	}

	int len = ft_strlen(cpy);

	int count = 0;
	int i = -1;
	while (++i < comps->count)
	{
		if (ft_strncmp(comps->suggestions[i], cpy, len) != 0)
			continue ;
		if (ft_strlen(comps->suggestions[i]) <= len)
			continue ;
		comps->matches[count] = malloc(sizeof(char) * ft_strlen(comps->suggestions[i]) + 1);
		ft_strcpy(comps->matches[count], comps->suggestions[i]);
		count++;
	}
	comps->matches_count = count;
}

// sort comp->matches by length so we get shortest first
void sort_by_length(t_completions *comps)
{
	int i = 0;
	char *temp;

	while (i < comps->matches_count - 1 && i < MAX_MATCHES - 1)
	{
		int a = ft_strlen(comps->matches[i]);
		int b = ft_strlen(comps->matches[i + 1]);
		if (a > b)
		{
			temp = comps->matches[i];
			comps->matches[i] = comps->matches[i + 1];
			comps->matches[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}
