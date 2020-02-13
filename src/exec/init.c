/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:08 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 22:39:11 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				execute_pipeline(t_ast *ast)
{
	if (!ast->left)
		return (init_pipeline(ast, ast->parent->right));
	else
		return (execute_pipeline(ast->left));
}

int				execution_init(t_ast *ast)
{
	if (!ast)
		return (EXEC_OK);
	if (ast->token->type & T_SCOL)
	{
		execution_init(ast->left);
		execution_init(ast->right);
	}
	else if (ast->token->type & T_PIPE)
		execute_pipeline(ast);
	else if (~(ast->token->type & MASK_CTRL))
		execute_command(ast);
	return (EXEC_OK);
}
