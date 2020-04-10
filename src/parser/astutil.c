/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astutil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:09:49 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/10 14:49:13 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Create a new leaf to AST
**	Breakpoint is either control character or string
**	Mark the end of token list at breakpoint
*/

t_ast		*new_leaf(t_token **token)
{
	int		bp;
	t_ast	*new;

	if (!(new = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	new->token = *token;
	new->nbr_token = 1;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->type = (*token)->type;
	// ft_printf("cmd start [%s]\n", (*token)->data);
	bp = (*token)->type & MASK_OP ? MASK_STR : MASK_OP;
	while ((*token)->next && !((*token)->type & bp))
	{
		new->nbr_token++;
		*token = (*token)->next;
	}
	new->cmd_end = !(*token)->next ? (*token)->next : *token;
	// new->cmd_end ? ft_printf("cmd end [%s]\n", new->cmd_end->data) : ft_printf("cmd end (NULL)\n");
	return (new);
}

/*
**	Create a new node to AST (parent and two children)
*/

t_ast		*new_node(t_ast *left, t_ast *parent, t_ast *right)
{
	parent->left = left;
	parent->right = right;
	if (left)
		left->parent = parent;
	if (right)
		right->parent = parent;
	return (parent);
}

/*
**	Delete AST and tokens using suffix travel
*/

void		ast_del(t_ast **ast)
{
	if (!*ast || !ast)
		return ;
	ast_del(&(*ast)->left);
	ast_del(&(*ast)->right);
	free(*ast);
	*ast = NULL;
}
