/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/18 13:04:41 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		init_lexer(t_lexer **lexer)
{
	if (!(*lexer = ft_memalloc(sizeof(t_lexer))))
		exit_error(MALLOC_ERROR, STR_MALLOC_ERR);
	(*lexer)->head = NULL;
	(*lexer)->first = NULL;
	(*lexer)->last = NULL;
	(*lexer)->count = 0;
	(*lexer)->flags = 0;
}

/*
**	Add tokens to linked list:
**		Control tokens "|", ";", ">>", "<<", "<&", "<>", ">&", ">|", ">", "<"
**		Strings (parse quotes and dquotes)
**	Update count and flags to t_lexer
*/

void			tokenize(t_lexer **lexer, char *input)
{
	int		i;

	i = 0;
	init_lexer(lexer);
	while (input[i])
	{
		if (ft_strchr(OPERATORS, input[i]))
			i += tokenize_operator(*lexer, &input[i]);
		else if (!ft_strncmp(OPT_LEXER, &input[i], ft_strlen(OPT_LEXER) - 1))
		{
			(*lexer)->flags |= DEBUG_LEXER;
			i += ft_strlen(OPT_LEXER);
		}
		else if (!ft_strncmp(OPT_AST, &input[i], ft_strlen(OPT_AST) - 1))
		{
			(*lexer)->flags |= DEBUG_AST;
			i += ft_strlen(OPT_AST);
		}
		else if (is_valid_char(input[i]))
			i += tokenize_string(*lexer, &input[i]);
		else
			i++;
	}
	(*lexer)->first = (*lexer)->head;
}
