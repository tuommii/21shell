/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/29 21:59:00 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Remove trailing semicolon from tokens
*/

static void	trailing_semicolon(t_lexer **lexer)
{
	t_token *token;
	t_token *prev;

	token = (*lexer)->head;
	while (token->next->next)
		token = token->next;
	free((*lexer)->last->data);
	free((*lexer)->last);
	token->next = NULL;
	(*lexer)->last = token;
	(*lexer)->count--;
}

/*
** Prompt for input with trailing pipe
*/

static void trailing_pipe(t_lexer **lexer)
{
	ft_printf("Implement case for trailing pipe\n");
	return ;
}


/*
**	1 - check lexer
**	2 - check syntax
**  3 - trailing control characters
*/

int			parser(t_lexer **lexer)
{
	if (!lexer || !*lexer || !(*lexer)->count)
		return (PARSER_ERROR);
	else if (check_syntax(*lexer) == PARSER_ERROR)
		return (PARSER_ERROR);
	if (!ft_strcmp((*lexer)->last->data, ";"))
		trailing_semicolon(lexer);
	else if (!ft_strcmp((*lexer)->last->data, "|"))
		trailing_pipe(lexer);
	return (PARSER_OK);
}
