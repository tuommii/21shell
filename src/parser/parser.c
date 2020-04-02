/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/02 13:15:41 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read in more input with open quotes
*/

static int	open_quote(t_lexer **lexer, int wquote)
{
	char	*input;
	t_line	*line;
	int		flag;
	char	err_msg;

	flag = 0;
	line = create_line_editor();
	add_token(*lexer, ft_strdup("\n"), STRING);
	while ((input = read_more(line, 1)) != NULL)
	{
		if (ft_lfind(input, wquote) != -1)
			flag = 1;
		add_token(*lexer, input, STRING);
		if (flag)
			break ;
	}
	if (flag)
		return (PARSER_OK);
	else
	{
		err_msg = (char)wquote;
		print_error(EOF_ERR, &err_msg);
		return (PARSER_ERROR);
	}
}

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
**	1 - check lexer
**	2 - check open quotes
**  3 - trailing control characters
**	4 - check syntax
*/

int			parser(t_lexer **lexer)
{
	int r;

	r = PARSER_OK;
	if (!lexer || !*lexer || !(*lexer)->count)
		r = PARSER_ERROR;
	else if ((*lexer)->flags & T_SQUOT)
		r = open_quote(lexer, 39);
	else if ((*lexer)->flags & T_DQUOT)
		r = open_quote(lexer, 34);
	else if (!ft_strcmp((*lexer)->last->data, ";"))
		r = trailing_semicolon(lexer);
	else if (!ft_strcmp((*lexer)->last->data, "|"))
		r = trailing_pipe(lexer);
	if (check_syntax(*lexer) == PARSER_ERROR)
		r = PARSER_ERROR;
	// remove quotes
	return (r);
}
