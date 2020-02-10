/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:15:49 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/10 17:16:23 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast		*new_leaf(t_token **token)
{
	t_ast	*new;

	if (!(new = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	new->token = *token;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->type = (*token)->type;
	return (new);
}

t_ast		*create_ast(t_token **token)
{
	t_ast	*root;

	root = new_leaf(token);
	return (root);
}
