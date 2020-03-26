/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:58:45 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/26 17:04:19 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Print out string array with index
*/

void 	array_debug(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("arr at index %d: [%s]\n", i, arr[i]);
		i++;
	}
}

/*
**	Apply infix traversal to print AST (grows to the right)
*/

void	ast_debug(t_ast *root, int ws)
{
	if (root == NULL)
		return ;
	ws += AST_COUNT;
	ast_debug(root->right, ws);
	ft_printf("\n");
	for (int i = AST_COUNT; i < ws; i++)
		ft_printf(" ");
	ft_printf("[%s][%d]\n", root->token->data, root->type);
	ast_debug(root->left, ws);
}

/*
** Print out lexer token count, flags and tokens
*/

void	lexer_debug(t_lexer *lexer)
{
	int		i;
	t_lexer	*tmp;

	i = 2;
	tmp = lexer;
	ft_printf("%s: [%d]\n", "token count", tmp->count);
	ft_printf("flags: ");
	ft_print_bits(tmp->flags, 16);
	ft_putchar('\n');
	while (tmp->head)
	{
		ft_printf("%s: [%s]\n", "token", tmp->head->data);
		if (tmp->head == tmp->last)
			break ;
		tmp->head = tmp->head->next;
		i++;
	}
}
