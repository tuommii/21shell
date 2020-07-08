/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:14:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/08 14:39:33 by mtuomine         ###   ########.fr       */
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
void filter(t_completer *ac,  char **arr, int count)
{
	if (!ac->word)
		return ;

	char *cpy = ac->word;
	if (cpy[0] == '$' && cpy[1])
	{
		cpy++;
	}
	int len = ft_strlen(cpy);
	// ft_printf("\nLEN: %d, WORD: %s\n", len, cpy);

	int i = 0;
	int match_count = 0;
	while (i < count)
	{
		//ft_printf("\n%s\n", ac->suggestions[i]);
		if (!arr[i])
		{
			i++;
			continue ;
		}
		if (ft_strncmp(arr[i], cpy, len) != 0)
		{
			i++;
			continue ;
		}
		if (ft_strlen(arr[i]) <= len)
		{
			i++;
			continue ;
		}
		ac->matches[match_count] = malloc(sizeof(char) * ft_strlen(arr[i]) + 1);
		ft_strcpy(ac->matches[match_count], arr[i]);
		match_count++;
		i++;
	}
	ac->matches_count = match_count;
}

// sort comp->matches by length so we get shortest first
void sort_by_length(t_completer *ac)
{
	int i = 0;
	char *temp;

	while (i < ac->matches_count - 1 && i < MAX_MATCHES - 1)
	{
		// TODO: Optimize
		int a = ft_strlen(ac->matches[i]);
		int b = ft_strlen(ac->matches[i + 1]);
		if (a > b)
		{
			temp = ac->matches[i];
			ac->matches[i] = ac->matches[i + 1];
			ac->matches[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}
