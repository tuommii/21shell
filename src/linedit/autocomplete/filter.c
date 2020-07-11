/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:14:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/11 16:25:45 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static char	*check_ctx_reset(char buffer[INPUT_BUFFER], int cursor, char *word)
{
	int		c;
	char	*ctx;

	if (cursor)
	{
		if (buffer[cursor - 1] == '|' || buffer[cursor - 1] == ';')
		{
			ctx = ft_strdup(CTX_EXEC);
			free(word);
			return (ctx);
		}
		c = cursor - ft_strlen(word);
		if (c)
			c--;
		while (c && buffer[c] == ' ')
			c--;
		if (c && (buffer[c] == '|' || buffer[c] == ';'))
		{
			ctx = ft_strdup(CTX_EXEC);
			free(word);
			return (ctx);
		}
	}
	return (NULL);
}

char		*get_context(char buffer[INPUT_BUFFER], int cursor)
{
	char *word;
	char *ctx;

	if (!(word = get_word_at(buffer, cursor)))
		return (NULL);
	if ((ctx = check_ctx_reset(buffer, cursor, word)))
		return (ctx);
	if (word[0] == '\0' || (ft_strlen(word) - cursor) <= 0)
		ctx = ft_strdup(CTX_EXEC);
	else if (word[0] == '$')
		ctx = ft_strdup(CTX_ENV);
	else if (word[0] == '-')
		ctx = ft_strdup(CTX_FLAG);
	else if (word[0] == '|' || word[0] == ';')
		ctx = ft_strdup(CTX_EXEC);
	else if (!cursor && buffer[cursor] == ' ')
		ctx = ft_strdup(CTX_EXEC);
	else
		ctx = ft_strdup(CTX_PATH);
	free(word);
	return (ctx);
}

void		filter(t_completer *ac, char **arr, int count)
{
	char	*cpy;
	size_t	len;
	int		i;

	cpy = ac->word;
	if (cpy[0] == '$' && cpy[1])
		cpy++;
	len = ft_strlen(cpy);
	i = 0;
	ac->matches_count = 0;
	while (i < count)
	{
		if (!arr[i] || ft_strlen(arr[i]) <= len)
			i++;
		else if (ft_strncmp(arr[i], cpy, len) != 0)
			i++;
		else
		{
			ac->matches[ac->matches_count] = \
			malloc(sizeof(char) * ft_strlen(arr[i]) + 1);
			ft_strcpy(ac->matches[ac->matches_count], arr[i]);
			ac->matches_count++;
			i++;
		}
	}
}

void		sort_by_length(t_completer *ac)
{
	int		i;
	char	*temp;
	int		a;
	int		b;

	i = 0;
	while (i < ac->matches_count - 1 && i < MAX_MATCHES)
	{
		a = ft_strlen(ac->matches[i]);
		b = ft_strlen(ac->matches[i + 1]);
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
