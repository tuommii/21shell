/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:23:11 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/07 13:44:35 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			parse_dollar(char **data)
{
	int		i;
	char	*tmp;
	char	*var;
	char	*value;

	i = 1;
	tmp = *data;
	while ((tmp = ft_strchr(tmp, '$')))
	{
		while (tmp[i] != '\0' && tmp[i] != '$' && tmp[i] != '"'
				&& !ft_isspace(tmp[i]))
			i++;
		var = ft_strsub(tmp, 0, i);
		if ((value = getenv(var + 1)))
		{
			*data = ft_strreplace(*data, var, value);
			tmp = *data;
		}
		tmp++;
		i = 1;
		free(var);
	}
}

static void			parse_tilde(char **data)
{
	char	*tmp;
	char	*value;

	tmp = *data;
	while ((tmp = ft_strchr(tmp, '~')))
	{
		if ((value = getenv("HOME")))
		{
			*data = ft_strreplace(*data, "~", value);
			tmp = *data;
		}
		tmp++;
	}
}

/*
** Expand $ and ~ characters in tokens
*/

void	expand_tokens(t_lexer **lexer)
{
	t_token *token;

	token = (*lexer)->head;
	while (token)
	{
		if (token->type & T_STR)
		{
			parse_dollar(&token->data);
			parse_tilde(&token->data);
		}
		token = token->next;
	}
}