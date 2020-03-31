/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 12:07:32 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 12:07:51 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		tokenize_string(t_lexer *lexer, char *input)
{
	int i;
	int	j;

	i = 0;
	while (str_valid_char(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
		{
			j = i;
			i += next_quote(&input[i + 1], input[i]);
			add_token(lexer, ft_strsub(&input[j + 1], 0, i), STRING);
			return (i + 2);
		}
		i++;
	}
	add_token(lexer, ft_strsub(input, 0, i), STRING);
	return (i);
}