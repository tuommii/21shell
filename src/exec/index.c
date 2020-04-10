/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:08 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/10 14:44:48 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Recurse until bottom of the tree is reached, or node is pipe
*/

static int		recurse_semicolons(t_ast *ast)
{
	execution_init(ast->left);
	return (execution_init(ast->right));
}

/*
** Recurse to the leftmost leaf and initialize pipeline
*/

static int		recurse_pipes(t_ast *ast)
{
	if (!ast->left)
		return (execute_pipeline(ast, ast->parent->right));
	else
		return (recurse_pipes(ast->left));
}

/*
** Recurse to the bottom of the tree based on hierarchy of commands
*/

int				execution_init(t_ast *ast)
{
	// ft_printf("!!EXEC INIT!! [%s]\n", ast->token->data);
	if (ast->token->type & T_SCOL)
		return (recurse_semicolons(ast));
	else if (ast->token->type & T_PIPE)
		return (recurse_pipes(ast));
	else if (~(ast->token->type & MASK_CTRL))
		return (execute_command(ast, NORMAL_EXEC));
	else
		return (EXEC_OK);
}
