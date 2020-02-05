/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/05 16:40:38 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_syntax(t_lexer *lexer)
{
	int		stack;
	t_token *token;

	token = lexer->head;
	while (token)
	{
		if (MASK_OP & token->type)
			ft_printf("\t[It's an operator!]");
		else if (MASK_REDIR & token->type)
			ft_printf("\t[It's a redirection!]");
		else if (T_STR & token->type)
			ft_printf("\t[It's a string!]");
		token = token->next;
	}
	return (0);
}

/*
**	1 - check lexer
**	2 - check syntax
*/

int		parser(t_lexer **lexer)
{
	if (!lexer || !*lexer || !(*lexer)->count)
		return (1);
	if (check_syntax(*lexer))
		return (2);
	return (PARSER_OK);
}
