/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:21:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/07 14:10:12 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read in more input with open quotes
*/

int		open_quote(t_lexer **lexer, int wquote)
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
** Heredoc: Read from stdin, must start and end with with same charset (EOL, etc.) 
*/

int		heredoc(t_lexer **lexer)
{
	int		flag;
	char 	*eol;
	char	*tmp;
	char	*input;
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