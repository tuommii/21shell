/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:08 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 11:47:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			lnr_exection(t_ast *ast, int *r)
{
	if (ast == NULL)
		return ;
	lnr_exection(ast->left, r);

	// if (ast->token->type & MASK_CTRL)
	// 	ft_printf(" | passing [%s]", ast->token->data);
	// else if (!ast->parent)
	// 	ft_printf(" | execute [%s]", ast->token->data);
	// else if (ast->parent && ast->parent->right)
	// 	ft_printf(" | execute [%s %s %s]", ast->token->data, ast->parent->token->data, ast->parent->right->token->data);
	while (ast->token)
	{
		ft_printf(" [%s]", ast->token->data);
		ast->token = ast->token->next;
	}
	// kato parent node. Tokenin perusteella oikee execute function pointer (tsekkaa printf)
	lnr_exection(ast->right, r);
}

int				exec_semicol(t_ast *ast)
{
	ft_execute(ast->left);
	return (ft_execute(ast->right));
}

int				exec_pipe(t_ast *ast)
{
	// if (!ast->left)
	// 	return (ft_launch_pipeline(ast, ast->parent->right));
	// else
	// 	return (ft_execute_pipeline(ast->left));
}

int				execute(t_ast *ast)
{
	if (!ast)
		return (EXEC_OK);
	if (ast->token->type & T_SCOL)
		exec_semicol(ast);
	else if (ast->token->type & T_PIPE)
		exec_pipe(ast);
	else if (!(ast->token->type & MASK_CTRL))
		return (exec_cmd(ast));
	return (EXEC_OK);
}
