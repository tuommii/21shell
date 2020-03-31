/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 12:04:06 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 12:47:38 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void		ft_get_io_number(t_lexer *lexer, char *line)
// {
// 	if (lexer->last && ft_isnumber(lexer->last->str) &&
// 			ft_strncmp(line - ft_strlen(lexer->last->str),
// 				lexer->last->str, ft_strlen(lexer->last->str)) == 0)
// 	{
// 		lexer->last->token_type = IO_NUMBER;
// 	}
// }

/*
** If operator index is less than 6, create normal token,
** 		otherwise create IO redirection
*/

int			ft_isnumeric(char *str)
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

static int	create_token(t_lexer *lexer, char *input, char *operator, int i)
{
	(void)input;
	if (i < 2)
		add_token(lexer, ft_strdup(operator), i);
	else
	{
		if (lexer->last)
		{
			if (ft_isnumeric(lexer->last->data))
			ft_printf("last token: %s\n", lexer->last->data);
		}
		add_token(lexer, ft_strdup(operator), i);
	}
	return (ft_strlen(operator));
}

/*
** Loop through OPERATOR_ARR and create a new token with the correct operator.
*/

int			tokenize_operator(t_lexer *lexer, char *input)
{
	int		i;
	char	operator[OP_SLOTS][OP_LEN] = {OPERATOR_ARR};

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(input, operator[i], ft_strlen(operator[i])))
		{
			return (create_token(lexer, input, operator[i], i));
		}
		i++;
	}
	return (1);	
}