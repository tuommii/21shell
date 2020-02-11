/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:08 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/11 19:13:31 by srouhe           ###   ########.fr       */
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

/*
**		Executes commands in 21sh.
**			- Infix travel through the tree while executing
*/

int				execute(t_ast *ast)
{
	int	r;

	r = 0;
	if (!ast)
		return (EXEC_OK);
	// lnr_exection(ast, &r);
	if (r == EXEC_ERROR)
		return (EXEC_ERROR);
	return (EXEC_OK);
}
