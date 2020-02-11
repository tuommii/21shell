/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:15:49 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/11 19:26:44 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ============== Grammar (BNF) ==============
**
** 	semicol:			pipe ((T_SCOL) pipe)*
** 	pipe: 				command ((T_PIPE) command)*
** 	command:			(T_STR)+ (MASK_REDIR T_STR)*
*/

/*
** Within a same level of precedence, check to see if there is another occurence
** of a sign of the precedence level (see grammar).
** If so, built the tree upward, the actual node is the left wing.
** Else, finish building the tree down to the right.
** Easy to add more levels when || && etc. operators come in play
*/

t_ast	*pipe_level(t_token **token)
{
	t_ast	*root;

	root = new_leaf(token);
	ft_printf("    [DEBUG PIPE %s]", (*token)->data);
	while ((*token)->type & T_PIPE)
	{
		ft_printf("    [PIPE %s]", (*token)->data);
		root = new_node(root, new_leaf(token), new_leaf(token));
	}
	return (root);
}

t_ast	*semicol_level(t_token **token)
{
	t_ast	*root;

	root = pipe_level(token);
	while ((*token)->type & T_SCOL)
	{
		ft_printf("    [SCOL %s]", (*token)->data);
		root = new_node(root, new_leaf(token), pipe_level(token));
		ft_printf("    [DEBUG SCOL %s]", (*token)->data);
	}
	return (root);
}

t_ast		*create_ast(t_token **token)
{
	int		i;
	t_ast	*root;

	i = 0;
	root = semicol_level(token);
	// root = new_leaf(token);
	// while ((*token)->next)
	// 	root = new_node(root, new_leaf(token), new_leaf(token));
	return (root);
}
