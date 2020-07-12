/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:23:11 by srouhe            #+#    #+#             */
/*   Updated: 2020/07/12 18:42:16 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*helper(char *var)
{
	if (!ft_strcmp(var, "$?"))
		return (ft_itoa(g_sh.status));
	else if (get_env(var + 1))
		return (ft_strdup(get_env(var + 1)));
	else
		return (NULL);
}

static void			clean(char *value, char *tmp)
{
	free(value);
	ft_strdel(&tmp);
}

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
		value = helper(var);
		if (value)
		{
			tmp = *data;
			*data = ft_strreplace(tmp, var, value);
			clean(value, tmp);
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
		if ((value = get_env("HOME")))
		{
			tmp = *data;
			*data = ft_strreplace(tmp, "~", value);
			ft_strdel(&tmp);
			tmp = *data;
		}
		tmp++;
	}
}

/*
** Expand $ and ~ characters in tokens and heredocs
*/

void				expand_tokens(t_lexer **lexer)
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
		if (token->heredoc)
		{
			parse_dollar(&token->heredoc);
			parse_tilde(&token->heredoc);
		}
		token = token->next;
	}
}
