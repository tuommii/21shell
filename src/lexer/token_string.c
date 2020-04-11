/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 12:07:32 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/11 11:12:42 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Parse quotes and check open squotes and dquotes
*/

static int	check_quoting(t_lexer *lexer, char *input, int i)
{
	int j;
	int	quot;

	j = i;
	quot = next_quote(&input[i + 1], input[i]);
	if (quot == -1 && input[i] == 34)
	{
		add_token(lexer, ft_strsub(input, 0, ft_strlen(input)), F_DQUOTE);
		return (ft_strlen(input));
	}
	else if (quot == -1 && input[i] == 39)
	{
		add_token(lexer, ft_strsub(input, 0, ft_strlen(input)), F_SQUOTE);
		return (ft_strlen(input));
	}
	else
	{
		i += quot;
		add_token(lexer, ft_strsub(&input[j + 1], 0, i), STRING);
		return (i + 2);
	}
}

/*
** Make a string, file or io number token
*/

int			tokenize_string(t_lexer *lexer, char *input)
{
	int i;

	i = 0;
	while (is_valid_char(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
		{
			return (check_quoting(lexer, input, i));
		}
		i++;
	}
	if (lexer->last && lexer->last->type & MASK_REDIR && str_isnumeric(input))
		add_token(lexer, ft_strsub(input, 0, i), IO_NUMBER);
	else if (lexer->last && lexer->last->type & MASK_REDIR && !ft_strcmp(input, "-"))
		add_token(lexer, ft_strsub(input, 0, i), DASH);
	else if (lexer->last && lexer->last->type & MASK_REDIR)
		add_token(lexer, ft_strsub(input, 0, i), FILENAME);
	else
		add_token(lexer, ft_strsub(input, 0, i), STRING);
	return (i);
}