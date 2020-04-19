/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:21:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/19 18:58:01 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		*read_open_quote(char **data, int wquote)
{
	t_line	*line;
	char	*input;
	char	*tmp;
	int		flag;

	flag = 0;
	tmp = *data;
	*data = ft_strjoin(tmp, "\n");
	ft_strdel(&tmp);
	line = create_line_editor();
	while ((input = read_more(line, 1)) != NULL)
	{
		if (ft_lfind(input, wquote) != -1)
			flag = 1;
		tmp = *data;
		*data = ft_strjoin(tmp, input);
		ft_strdel(&tmp);
		free(input);
		if (flag)
			break ;
	}
	free_line_editor(line);
	if (!flag)
		ft_strdel(data);
}

/*
** Read in more input with open quotes
*/

int				open_quote(t_lexer **lexer, int wquote)
{
	char	*new;
	char	err_msg;

	read_open_quote(&(*lexer)->last->data, wquote);
	if ((*lexer)->last->data)
	{
		(*lexer)->last->data[ft_strlen((*lexer)->last->data) - 1] = '\0';
		remove_quotes((*lexer)->head, wquote);
		return (PARSER_OK);
	}
	else
	{
		err_msg = (char)wquote;
		print_error(EOF_ERR, &err_msg);
		return (PARSER_ERROR);
	}
}
