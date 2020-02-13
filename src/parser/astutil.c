/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astutil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:09:49 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 11:35:00 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Create a new leaf to AST and move token accordingy
*/

t_ast		*new_leaf(t_token **token)
{
	int		bp;
	t_ast	*new;

	if (!(new = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	new->token = *token;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->type = (*token)->type;
	if ((*token)->type & MASK_OP)
		bp = MASK_STR;
	else
		bp = MASK_OP;
	while ((*token)->next && !((*token)->type & bp))
		*token = (*token)->next;
	if (!(*token)->next)
		new->cmd_end = (*token)->next;
	else
		new->cmd_end = *token;
	return (new);
}

/*
**	Create a new node to AST: parent and two children
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
	t_token *tmp;

	if (!*ast || !ast)
		return ;
	ast_del(&(*ast)->left);
	ast_del(&(*ast)->right);
	free(*ast);
	*ast = NULL;
}
