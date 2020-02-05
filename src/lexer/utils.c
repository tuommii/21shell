/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 09:45:18 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/05 10:29:41 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Checks if c is printable, excluding space and not an operator
*/

int		valid_str(char c)
{
	return ((c <= 126 && c > 32) && !ft_strchr(OPERATORS, c) ? 1 : 0);
}

/*
**	Jumps to next single or double quote
*/

int		jump_to_next_quote(char *input, int q)
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_printf("char as int [%d] ", (int)input[i]);
		if ((int)input[i] == q)
			break ;
		i++;
	}
	return (i);
}