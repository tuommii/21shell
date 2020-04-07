/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/07 14:21:25 by srouhe           ###   ########.fr       */
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
** Prompt for more input with trailing pipe
*/

static int	trailing_pipe(t_lexer **lexer)
{
	char	*input;
	t_line	*line;
	
	line = create_line_editor();
	if (!(input = read_more(line, 0)))
		return (PARSER_ERROR);
	add_token(*lexer, input, STRING);
	return (PARSER_OK);
}

/*
**	1 - check lexer and token count
**	2 - check open quoting & clean quotes
**  3 - check trailing semicolon, pipe and <<
**	4 - expand $ ~
**	5 - check syntax
*/

int			parser(t_lexer **lexer)
{
	int r;

	if (!lexer || !*lexer || !(*lexer)->count)
		return (PARSER_ERROR);
	else if ((*lexer)->flags & T_SQUOT)
		r = open_quote(lexer, 39);
	else if ((*lexer)->flags & T_DQUOT)
		r = open_quote(lexer, 34);
	(*lexer)->flags & T_SQUOT ? remove_quotes((*lexer)->head, 39) : PASS;
	(*lexer)->flags & T_DQUOT ? remove_quotes((*lexer)->head, 34) : PASS;
	if ((*lexer)->count > 1)
	{
		if ((*lexer)->last->type & T_SCOL)
			r = trailing_semicolon(lexer);
		else if ((*lexer)->last->type & T_PIPE)
			r = trailing_pipe(lexer);
		else if ((*lexer)->last->prev->type & T_DLARR)
			r = heredoc(lexer);
	}
	expand_tokens(lexer);
	r = check_syntax(*lexer);
	return (r);
}
