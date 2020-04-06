/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/06 18:25:22 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read in more input with open quotes
*/

static int	open_quote(t_lexer **lexer, int wquote)
{
	char	*input;
	char	*tmp;
	t_line	*line;
	int		flag;
	char	err_msg;

	flag = 0;
	line = create_line_editor();
	tmp = (*lexer)->last->data;
	(*lexer)->last->data = ft_strjoin((*lexer)->last->data, "\n");
	free(tmp);
	while ((input = read_more(line, 1)) != NULL)
	{
		if (ft_lfind(input, wquote) != -1)
			flag = 1;
		tmp = (*lexer)->last->data;
		(*lexer)->last->data = ft_strjoin((*lexer)->last->data, input);
		free(tmp);
		free(input);
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
	return (PARSER_OK);
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
** Heredoc: Read from stdin, must start and end with with same charset (EOL, etc.) 
*/

static int	heredoc(t_lexer **lexer)
{
	int		flag;
	char 	*eol;
	char	*tmp;
	char	*input;
	char	*heredoc;
	t_line	*line;

	eol = ft_strdup((*lexer)->last->data);
	(*lexer)->last = (*lexer)->last->prev;
	free((*lexer)->last->next->data);
	free((*lexer)->last->next);
	(*lexer)->last->next = NULL;
	flag = 0;
	line = create_line_editor();
	ft_strclr((*lexer)->last->data);
	tmp = (*lexer)->last->data;
	(*lexer)->last->data = ft_strjoin((*lexer)->last->data, "\n");
	free(tmp);
	while ((input = read_more(line, 1)) != NULL)
	{
		if (!ft_strncmp(input, eol, ft_strlen(eol)))
		{
			free(input);
			flag = 1;
			break ;
		}
		tmp = (*lexer)->last->data;
		(*lexer)->last->data = ft_strjoin((*lexer)->last->data, input);
		free(tmp);
		free(input);
	}
	tmp = (*lexer)->last->data;
	(*lexer)->last->data = ft_strreplace((*lexer)->last->data, eol, "");
	free(tmp);
	if (flag)
	{
		free(eol);
		return (PARSER_OK);
	}
	else
	{
		print_error(HEREDOC_ERR, eol);
		free(eol);
		return (PARSER_ERROR);
	}
}

/*
**	1 - check lexer
**	2 - check open quoting
**  3 - check trailing semicolon, pipe and <<
**	4 - check syntax
**	5 - clean quotes
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
	(*lexer)->flags & T_SQUOT ? remove_quotes((*lexer)->head, T_SQUOT, 39) : PASS;
	(*lexer)->flags & T_DQUOT ? remove_quotes((*lexer)->head, T_DQUOT, 34) : PASS;

	if ((*lexer)->count > 1)
	{
		if ((*lexer)->last->type & T_SCOL)
			r = trailing_semicolon(lexer);
		else if ((*lexer)->last->type & T_PIPE)
			r = trailing_pipe(lexer);
		else if ((*lexer)->last->prev->type & T_DLARR)
			r = heredoc(lexer);
	}

	if (check_syntax(*lexer) == PARSER_ERROR)
		r = PARSER_ERROR;
	return (r);
}
