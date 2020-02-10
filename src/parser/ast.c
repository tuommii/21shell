/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:15:49 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/10 17:49:20 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	if ((*token)->type & MASK_CTRL)
		bp = T_STR;
	else
		bp = MASK_CTRL;
	while ((*token)->next && !((*token)->type & bp))
		*token = (*token)->next;
	return (new);
}

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

t_ast		*create_ast(t_token **token)
{
	t_ast	*root;

	root = new_leaf(token);
	root = new_node(root, new_leaf(token), new_leaf(token));
	root = new_node(root, new_leaf(token), new_leaf(token));
	root = new_node(root, new_leaf(token), new_leaf(token));
	return (root);
}
