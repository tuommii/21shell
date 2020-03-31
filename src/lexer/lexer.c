/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 15:05:50 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		lexer_del(t_lexer **lexer)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = (*lexer)->head;
	while (tmp)
	{
		ft_strdel(&tmp->data);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	(*lexer)->head = NULL;
	(*lexer)->last = NULL;
	free(*lexer);
	*lexer = NULL;
}

/*
**	Add tokens to linked list:
**		Control tokens "|", ";", ">>", "<<", "<&", "<>", ">&", ">|", ">", "<" 
**		Strings (parse quotes and dquotes)
**	Update count and flags to t_lexer
*/

void		tokenize(t_lexer **lexer, char *input)
{
	int		i;

	i = 0;
	if (!(*lexer = ft_memalloc(sizeof(t_lexer))))
		return ;
	(*lexer)->head = NULL;
	(*lexer)->last = NULL;
	(*lexer)->count = 0;
	(*lexer)->flags = 0;
	while (input[i])
	{
		if (ft_strchr(OPERATORS, input[i]))
			i += tokenize_operator(*lexer, &input[i]);
		else if (!ft_strncmp(OPT_LEXER, &input[i], ft_strlen(OPT_LEXER) - 1))
		{
			(*lexer)->flags |= DEBUG_LEXER;
			i += ft_strlen(OPT_LEXER);
		}
		else if (!ft_strncmp(OPT_AST, &input[i], ft_strlen(OPT_AST) - 1))
		{
			(*lexer)->flags |= DEBUG_AST;
			i += ft_strlen(OPT_AST);
		}
		else if (str_valid_char(input[i]))
			i += tokenize_string(*lexer, &input[i]);
		else
			i++;
	}
}
