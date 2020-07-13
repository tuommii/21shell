/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:09:11 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/19 18:57:25 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*read_heredoc(char *r, char *d)
{
	char	*in;

	while ((in = read_more(g_sh.line, 1)) != NULL)
	{
		if (!ft_strncmp(in, d, ft_strlen(d) - 1) && in[ft_strlen(d)] == '\n')
		{
			free(in);
			return (r);
		}
		if (!r)
			r = ft_strdup(in);
		else
		{
			r = ft_realloc(r, ft_strlen(r), ft_strlen(r) + ft_strlen(in));
			r = ft_strncat(r, in, ft_strlen(in));
		}
		free(in);
	}
	r ? free(r) : PASS;
	return (NULL);
}

/*
** Read input in to [<<] and recurse to parser to check if more heredoc's
*/

int			check_heredoc(t_lexer **lexer)
{
	char	*new;
	t_token	*head;

	head = (*lexer)->head;
	while ((*lexer)->head)
	{
		if ((*lexer)->head->type & T_DLARR && !(*lexer)->head->heredoc)
		{
			if ((new = read_heredoc((*lexer)->head->heredoc, \
									(*lexer)->head->next->data)) != NULL)
			{
				(*lexer)->head->heredoc = new;
				(*lexer)->head = head;
				return (parser(lexer));
			}
			else
			{
				print_error(HEREDOC_ERR, (*lexer)->head->next->data);
				return (PARSER_ERROR);
			}
		}
		(*lexer)->head = (*lexer)->head->next;
	}
	(*lexer)->head = head;
	return (PARSER_OK);
}
