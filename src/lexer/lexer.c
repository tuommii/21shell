/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/05 10:29:37 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int		tokenize_operator(t_lexer *lexer, char *input)
{
	int		i;
	char	operator[6][3] = {"|", ";", ">>", "<<", "<", ">"};

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(input, operator[i], ft_strlen(operator[i]) - 1))
		{
			add_token(lexer, operator[i]);
			return (ft_strlen(operator[i]));
		}
		i++;
	}
	return (1);	
}

int		tokenize_str(t_lexer *lexer, char *input)
{
	int i;

	i = 0;
	while (valid_str(input[i]))
	{
		if ((int)input[i] == 34)
			i += jump_to_next_quote(&input[i + 1], 34);
		else if ((int)input[i] == 39)
			i += jump_to_next_quote(&input[i + 1], 39);
		i++;
	}
	add_token(lexer, ft_strsub(input, 0, i));
	return (i);
}

void	tokenize(t_lexer **lexer, char *input)
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
		if (ft_strchr(OPERATORS, input[i])) // different functions for different tokens
			i += tokenize_operator(*lexer, &input[i]);
		else if (valid_str(input[i]))
			i += tokenize_str(*lexer, &input[i]);
		else
			i++;
		// else if (ft_isprint(*input) && !ft_isspace(*input) && !ft_strchr(OPERATORS, *input))
		// 	ft_printf("hoo haa");
	}
}