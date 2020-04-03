/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 12:07:32 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/03 10:03:09 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Parse quotes and check open squotes and dquotes
*/

int		tokenize_string(t_lexer *lexer, char *input)
{
	int i;
	int	j;
	int flag;
	int	quot;

	i = 0;
	flag = STRING;
	while (str_valid_char(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
		{
			j = i;
			quot = next_quote(&input[i + 1], input[i]);
			if (quot == -1 && input[i] == 34)
				flag = F_DQUOTE;
			else if (quot == -1 && input[i] == 39)
				flag = F_SQUOTE;
			else
			{
				i += quot;
				add_token(lexer, ft_strsub(&input[j + 1], 0, i), flag);
				return (i + 2);
			}
		}
		i++;
	}
	add_token(lexer, ft_strsub(input, 0, i), flag);
	return (i);
}