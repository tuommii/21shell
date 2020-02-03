/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/03 22:16:12 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static void	print_lexer_debug(t_lexer *lexer)
{
	ft_putstr_fd(tgoto(CM, 0, 0), 0);
	tputs(CE, 1, print_char);
	ft_printf("%20s: [%d]", "token count", lexer->count);
	ft_putstr_fd(tgoto(CM, 0, 1), 0);
	while (lexer->head)
	{
		ft_printf("%20s: [%s]", "lexer head", lexer->head->data);
		lexer->head = lexer->head->next;
	}
	ft_printf("\033[u");
}

int		add_token(t_lexer *lexer, char *data)
{
	// add new token to lexer and update info, keep track of head and last
	t_token	*token;

	if (!(token = ft_memalloc(sizeof(t_token))))
		return (0);
	token->data = data;
	if (!lexer->head)
	{
		lexer->head = token;
		lexer->last = token;
	}
	else
	{
		while (lexer->last)
			lexer->last = lexer->last->next;
		lexer->last = token;
	}
	lexer->count++;
	print_lexer_debug(lexer);
	return (ft_strlen(data));
}

int		get_operator(t_lexer *lexer, char *input)
{
	int		i;
	char	operator[7][3] = {";", "|", "<<", "<", ">>", ">", "\0"};

	i = 0;
	while (operator[i])
	{
		if (ft_strnequ(input, operator[i], ft_strlen(operator[i])))
			return (add_token(lexer, ft_strdup(operator[i])));
		i++;
	}
	return (0);	
}

void	tokenize(t_shell *sh)
{
	char	*input;
	t_lexer	*lexer;

	if (!(lexer = ft_memalloc(sizeof(t_lexer))))
		exit_error(sh, 2);
	input = sh->input;
	while (*input)
	{
		if (ft_strchr(OPERATORS, *input)) // different functions for different tokens
			input += get_operator(lexer, input);
		// else if (ft_isprint(*input) && !ft_isspace(*input) && !ft_strchr(OPERATORS, *input))
		// 	add_word(lexer, input);
		input++;
	}
	// print_lexer_debug(lexer);
}