/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 09:45:18 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 13:33:18 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Checks if c is printable, excluding space and not an operator
*/

int		str_valid_char(char c)
{
	return ((c <= 126 && c > 32) && !ft_strchr(OPERATORS, c) ? 1 : 0);
}

/*
**	Jumps to next single or double quote
**	to-do: Handle open quotes
*/

int		next_quote(char *input, int q)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != q)
		i++;
	// ft_printf("inside quotes [%d] ", i);
	return (i);
}

int		str_isnumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
