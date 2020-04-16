/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:21:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/16 12:04:45 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*read_open_quote(char *r, int wquote)
{
	t_line	*line;
	char	*input;
	int		flag;

	flag = 0;
	r = ft_realloc(r, ft_strlen(r), ft_strlen(r) + 1);
	r = ft_strncat(r, "\n", 1);
	line = create_line_editor();
	while ((input = read_more(line, 1)) != NULL)
	{
		if (ft_lfind(input, wquote) != -1)
			flag = 1;
		r = ft_realloc(r, ft_strlen(r), ft_strlen(r) + ft_strlen(input));
		r = ft_strncat(r, input, ft_strlen(input));
		free(input);
		if (flag)
			break ;
	}
	free_history(&line->hist);
	free(line);
	if (flag)
		return (r);
	else
		return (NULL);
}

/*
** Read in more input with open quotes
*/

int				open_quote(t_lexer **lexer, int wquote)
{
	char	*new;
	char	err_msg;

	if ((new = read_open_quote((*lexer)->last->data, wquote)) != NULL)
	{
		ft_strdel(&(*lexer)->last->data);
		new[ft_strlen(new) - 1] = '\0';
		(*lexer)->last->data = new;
		return (PARSER_OK);
	}
	else
	{
		err_msg = (char)wquote;
		print_error(EOF_ERR, &err_msg);
		return (PARSER_ERROR);
	}
}
