/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/16 16:30:38 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	free_history(&line->hist);
	free(line);
	return (PARSER_OK);
}

/*
**	1 - check lexer and token count
**	2 - check syntax
**	3 - check open quoting and read more
**	4 - check heredoc and read to all of them
**  5 - check trailing semicolon, pipe and <<
**	6 - clean quotes
**	7 - expand $ ~
*/

int			parser(t_lexer **lexer)
{
	int r;

	if (!lexer || !*lexer || !(*lexer)->count)
		return (PARSER_ERROR);
	if ((r = check_syntax(*lexer)) == PARSER_ERROR)
		return (PARSER_ERROR);
	if ((*lexer)->flags & T_SQUOT)
		r = open_quote(lexer, S_QUOTE);
	else if ((*lexer)->flags & T_DQUOT)
		r = open_quote(lexer, D_QUOTE);
	else if ((*lexer)->flags & T_DLARR)
		r = check_heredoc(lexer);
	if ((*lexer)->count > 1)
	{
		if ((*lexer)->last->type & T_SCOL)
			r = remove_last_token(lexer);
		else if ((*lexer)->last->type & T_PIPE)
			r = trailing_pipe(lexer);
	}
	(*lexer)->flags & T_SQUOT ? remove_quotes((*lexer)->head, S_QUOTE) : PASS;
	(*lexer)->flags & T_DQUOT ? remove_quotes((*lexer)->head, D_QUOTE) : PASS;
	expand_tokens(lexer);
	return (r);
}
