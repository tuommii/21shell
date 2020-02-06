/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:12:44 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/06 21:48:26 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	syntax_error(char *token)
{
	ft_printf("\t21sh: syntax error near unexpected token `%s'", token);
}

/*
**	Check previous and current value of the token stack
**	to-do: check differences between shells (bash / zsh)
*/

int 	check_stack(int prev, int curr)
{
	// ft_printf("  stack prev [%d]", prev);
	// ft_printf("  stack curr [%d]", curr);
	if (!prev && curr & MASK_OP)
		return (PARSER_ERROR);
	else if ((prev & MASK_REDIR || prev & MASK_OP) && (curr & MASK_REDIR || curr & MASK_OP))
		return (PARSER_ERROR);
	return (PARSER_OK);
}

/*
**	Loop over tokens and check the syntax
*/

int		check_syntax(t_lexer *lexer)
{
	int		top;
	int		stack[4096];
	char	*data;
	t_token *token;

	top = 0;
	stack[top] = 0;
	token = lexer->head;
	while (token)
	{
		data = token->data;
		stack[++top] = token->type;
		if ((check_stack(stack[top - 1], stack[top])) == PARSER_ERROR)
		{
			syntax_error(data);
			return (PARSER_ERROR);
		}
		token = token->next;
	}
	if (stack[top] & MASK_OP || stack[top] & MASK_REDIR)
	{
		syntax_error(data);
		return (PARSER_ERROR);
	}
	return (PARSER_OK);
}