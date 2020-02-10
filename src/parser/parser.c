/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/10 17:10:18 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Create list of commands from lexer tokens
*/

// void		add_command(t_token **head, t_ast **ast)
// {
// 	int		i;
// 	int		size;
// 	char	**args;
// 	t_ast	**tmp;

// 	i = 0;
// 	size = args_count(*head);
// 	args = (char **)ft_memalloc(size);
// 	// ft_printf("   token count [%d]", size);
// 	while (*head && (*head)->type & T_STR)
// 	{
// 		args[i] = ft_strdup((*head)->data);
// 		// ft_printf("   str token [%s]", head->data);
// 		*head = (*head)->next;
// 		i++;
// 	}
// 	// Check operators & redirections here
// 	args[i] = NULL;
// 	tmp = ast;
// 	while (*tmp)
// 		*tmp = (*tmp)->next;
// 	*tmp = new_leaf(args);
// }

void	parse_commands(t_lexer **lexer, t_ast **cmd)
{
	int		i;
	char	**tokens;
	t_token	*head;

	i = 0;
	tokens = (char **)ft_memalloc((*lexer)->count);
	head = (*lexer)->head;
	while (head)
	{
		tokens[i++] = ft_strdup(head->data);
		if (head->type & MASK_OP || head->type & MASK_REDIR || head->next == NULL)
			ft_printf("\t{op or redir here}");
		head = head->next;
	}
	tokens[i] = NULL;
	array_debug(tokens);
	if ((*lexer)->flags & MASK_OP || (*lexer)->flags & MASK_REDIR)
		ft_printf("\twe have operators!");
	else
		ft_printf("\tjust a single command!");
	// while (head)
	// {
	// add_command(&head, cmd);
	// ft_printf("\thead data: [%s]", head->data);
		// head = head->next;
	// }
}

/*
**	1 - check lexer
**	2 - check syntax
*/

int		parser(t_lexer **lexer)
{
	if (!lexer || !*lexer || !(*lexer)->count)
		return (PARSER_ERROR);
	else if (check_syntax(*lexer) == PARSER_ERROR)
		return (PARSER_ERROR);
	return (PARSER_OK);
}
