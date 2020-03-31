/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 12:22:08 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Remove trailing semicolon from tokens
*/

static int	trailing_semicolon(t_lexer **lexer)
{
	t_token *token;

	token = (*lexer)->head;
	while (token->next->next)
		token = token->next;
	free((*lexer)->last->data);
	free((*lexer)->last);
	token->next = NULL;
	(*lexer)->last = token;
	(*lexer)->count--;
	return (PARSER_OK);
}

/*
** Prompt for input with trailing pipe
*/

// static int	trailing_pipe(t_lexer **lexer)
// {
// 	t_line *line = create_line_editor();
// 	char *input;
// 	while (input = quote_loop(line) != NULL) {

// 	}

// 	// input = readin();
// 	ft_strdel(&((*lexer)->last->data));
// 	(*lexer)->last->data = input;
// 	return (PARSER_OK);
// }

/*
**	1 - check lexer
**	2 - check syntax
**  3 - trailing control characters
*/

int			parser(t_lexer **lexer)
{
	int r;

	r = PARSER_OK;
	if (!lexer || !*lexer || !(*lexer)->count)
		r = PARSER_ERROR;
	else if (check_syntax(*lexer) == PARSER_ERROR)
		r = PARSER_ERROR;
	else if (!ft_strcmp((*lexer)->last->data, ";"))
		r = trailing_semicolon(lexer);
	// else if (!ft_strcmp((*lexer)->last->data, "|"))
	// 	r = trailing_pipe(lexer);
	return (r);
}
