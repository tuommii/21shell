/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/24 15:27:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static void	print_lex(t_lexer *lexer, char *input)
{
	ft_putstr_fd(tgoto(CM, 0, 0), 0);
	tputs(CE, 1, print_char);
	ft_putstr_fd(tgoto(CM, 0, 0), 0);
	ft_printf("%10s: [%s]", "input", input);
	ft_putstr_fd(tgoto(CM, 1, 0), 0);
	// ft_printf("%10s: [%s]", "lexer head", lexer->head->data);
	ft_printf("\033[u");
}

void	hop(char **input)
{
	char	*cpy;

	cpy = *input;
	while (*cpy == ' ' || *cpy == '\n' || *cpy == '\t' || *cpy == '\r' || *cpy == '\v')
		cpy++;
}

int		get_operator(t_lexer *lexer, char *input)
{
	int		i;
	char	operator[11][3] = {";;", ";", "&&", "&", "||", "|", "<<", "<", ">>", ">", "\0"};

	i = 0;
	while (operator[i])
	{
		if (ft_strnequ(input, operator[i], ft_strlen(operator[i])))
		{
			print_lex(lexer, input);
			return (ft_strlen(operator[i]));
		}
		++i;
	}
	return (0);	

}

void	tokenize(t_shell *sh)
{
	char	*input;
	t_lexer	*lexer;

	lexer = ft_memalloc(sizeof(t_lexer));
	input = sh->input;
	while (*input)
	{
		if (ft_strchr(OPERATORS, *input))
			input += get_operator(lexer, input);
		// else if (ft_isprint(*input) && !ft_isspace(*input) && !ft_strchr(OPERATORS, *input))
		// 	add_word(lexer, input);
		input++;
	}
	// print_lex(lexer, input);
}