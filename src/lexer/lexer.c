/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/04 22:54:31 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int		get_operator(t_lexer *lexer, char *input)
{
	int		i;
	char	operator[6][3] = {"|", ";", ">>", "<<", "<", ">"};

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(input, operator[i], ft_strlen(operator[i]) - 1))
		{
			ft_printf("       [operator %s]\n", operator[i]);
			return (add_token(lexer, operator[i]));
		}
		i++;
	}
	return (1);	
}

void	tokenize(t_lexer **lexer, char *input)
{
	int		i;

	i = 0;
	if (!(*lexer = ft_memalloc(sizeof(t_lexer))))
		return ;
	(*lexer)->head = NULL;
	(*lexer)->count = 0;
	(*lexer)->flags = 0;
	while (input[i])
	{
		if (ft_strchr(OPERATORS, input[i])) // different functions for different tokens
		{
			// ft_printf("               input: %s", &input[i]);
			i += get_operator(*lexer, &input[i]);
		}
		else
			i++;
		// else if (ft_isprint(*input) && !ft_isspace(*input) && !ft_strchr(OPERATORS, *input))
		// 	ft_printf("hoo haa");
	}
}