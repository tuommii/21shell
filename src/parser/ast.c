/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:15:49 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/10 18:47:03 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Creates abstract syntax tree. Very simple and unbalanced atm. Debug with --ast flag
*/

t_ast		*create_ast(t_token **token)
{
	int		i;
	t_ast	*root;

	i = 0;
	root = new_leaf(token);
	while ((*token)->next)
		root = new_node(root, new_leaf(token), new_leaf(token));
	return (root);
}
