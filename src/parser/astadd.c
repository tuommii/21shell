/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astadd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:09:49 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/11 23:01:42 by srouhe           ###   ########.fr       */
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
	// t_token	*stopper;

	if (!(new = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	new->token = *token;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->type = (*token)->type;
	if ((*token)->type & MASK_CTRL)
		bp = MASK_STR;
	else
		bp = MASK_CTRL;
	while ((*token)->next && !((*token)->type & bp))
	{
		// stopper = *token;
		*token = (*token)->next;
	}
	// stopper->next = NULL;
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
