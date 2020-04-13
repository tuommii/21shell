/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 12:04:06 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/13 19:30:45 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** If operator index is less than x, create normal token,
** 		otherwise create IO redirection
*/

static int	create_token(t_lexer *lexer, char *operator, int i)
{
	if (i < 2)
		add_token(lexer, ft_strdup(operator), i);
	else
	{
		if (lexer->last && str_isnumeric(lexer->last->data))
			lexer->last->type |= IO_NUM;
		add_token(lexer, ft_strdup(operator), i);
	}
	return (ft_strlen(operator));
}

/*
** Loop through OPERATOR_ARR and create a new token with the correct operator.
*/

int			tokenize_operator(t_lexer *lexer, char *input)
{
	int			i;
	static char	operator[OP_SLOTS][OP_LEN] = {OPERATOR_ARR};

	i = 0;
	while (i < OP_SLOTS)
	{
		if (!ft_strncmp(input, operator[i], ft_strlen(operator[i])))
			return (create_token(lexer, operator[i], i));
		i++;
	}
	return (1);
}
