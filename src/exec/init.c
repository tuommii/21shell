/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:08 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 16:04:50 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "exec.h"

// int				exec_semicol(t_ast *ast)
// {
// 	ft_execute(ast->left);
// 	return (ft_execute(ast->right));
// }

// int				exec_pipe(t_ast *ast)
// {
// 	// if (!ast->left)
// 	// 	return (ft_launch_pipeline(ast, ast->parent->right));
// 	// else
// 	// 	return (ft_execute_pipeline(ast->left));
// }

int				execution_init(t_ast *ast)
{
	if (!ast)
		return (EXEC_OK);
	if (ast->token->type & T_SCOL)
	{
		execution_init(ast->left);
		execution_init(ast->right);
	}
	// else if (ast->token->type & T_PIPE)
	// 	exec_pipe(ast);
	else if (~(ast->token->type & MASK_CTRL))
		return (execute_command(ast));
	return (EXEC_OK);
}
