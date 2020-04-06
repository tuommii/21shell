/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:12:44 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/06 18:30:13 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Check previous and current value of the token stack
**	to-do: check differences between shells (bash / zsh)
*/

static int 		check_stack(int prev, int curr, t_token *next)
{
	// ft_printf("  stack prev [%d]", prev);
	// ft_printf("  stack curr [%d]", curr);
	if (!prev && curr & MASK_OP)
		return (PARSER_ERROR);
	else if ((prev & MASK_REDIR || prev & MASK_OP) && (curr & MASK_REDIR || curr & MASK_OP))
		return (PARSER_ERROR);
	else if ((curr & MASK_REDIR || curr & T_DLARR) && next == NULL)
		return (PARSER_ERROR);
	return (PARSER_OK);
}

/*
**	Loop over tokens and check the syntax
*/

int				check_syntax(t_lexer *lexer)
{
	int		top;
	int		stack[4096];
	t_token *token;

	top = 0;
	stack[top] = 0;
	token = lexer->head;
	while (token)
	{
		stack[++top] = token->type;
		if ((check_stack(stack[top - 1], stack[top], token->next)) == PARSER_ERROR)
		{
			print_error(SYNTAX_ERR, token->data);
			return (PARSER_ERROR);
		}
		token = token->next;
	}
	return (PARSER_OK);
}
