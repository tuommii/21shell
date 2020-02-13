/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:15:49 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 11:01:04 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ============== Grammar (Backus–Naur form) ==============
**
** 	semicol:			pipe ((T_SCOL) pipe)*
** 	pipe: 				command ((T_PIPE) command)*
** 	command:			(T_STR)+ (MASK_REDIR T_STR)*
*/

/*
** AST is build by level of precedence (see BNF above)
** Easy to add more levels when || && etc. operators come in play in 42sh
*/

t_ast	*pipe_level(t_token **token)
{
	t_ast	*root;
	t_ast	*right;
	t_ast	*parent;

	root = new_leaf(token);
	// ft_printf("    [DEBUG PIPE %s]", (*token)->data);
	while ((*token)->type & T_PIPE)
	{
		parent = new_leaf(token);
		right = new_leaf(token);
		// ft_printf("    PIPE: [root %s] [parent %s] [right %s]", root->token->data, parent->token->data, right->token->data);
		root = new_node(root, parent, right);
	}
	return (root);
}

t_ast	*semicol_level(t_token **token)
{
	t_ast	*root;
	t_ast	*right;
	t_ast	*parent;

	root = pipe_level(token);
	while ((*token)->type & T_SCOL)
	{
		// ft_printf("    [SCOL %s]", (*token)->data);
		parent = new_leaf(token);
		right = pipe_level(token);
		// ft_printf("    SCOL: [root %s] [parent %s] [right %s]", root->token->data, parent->token->data, right->token->data);
		root = new_node(root, parent, right);
		// ft_printf("    [DEBUG SCOL %s]", (*token)->data);
	}
	return (root);
}

t_ast		*ast_create(t_token **token)
{
	t_ast	*root;

	root = semicol_level(token);
	return (root);
}
