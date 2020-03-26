/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 11:34:11 by srouhe           ###   ########.fr       */
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

static int	tokenize_operator(t_lexer *lexer, char *input)
{
	int		i;
	char	operator[OP_SLOTS][OP_LEN] = {OPERATOR_ARR};

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(input, operator[i], ft_strlen(operator[i]) - 1))
		{
			add_token(lexer, ft_strdup(operator[i]), i);
			return (ft_strlen(operator[i]));
		}
		i++;
	}
	return (1);	
}

static int	tokenize_string(t_lexer *lexer, char *input)
{
	int i;
	int	j;

	i = 0;
	while (str_valid_char(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
		{
			j = i;
			i += next_quote(&input[i + 1], input[i]);
			add_token(lexer, ft_strsub(&input[j + 1], 0, i), STRING);
			return (i + 2);
		}
		i++;
	}
	add_token(lexer, ft_strsub(input, 0, i), STRING);
	return (i);
}

/*
**	Add tokens to linked list:
**		Control tokens "|", ";", ">>", "<<", ">", "<"
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
