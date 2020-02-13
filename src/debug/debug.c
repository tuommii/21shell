/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:58:45 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 14:26:00 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 	array_debug(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("  arr at index %d: [%s]", i, arr[i]);
		i++;
	}
}

/*
**	Apply infix traversal to print AST (grows to the right)
*/

void	ast_debug(t_ast *root, int ws)
{
	if (root == NULL)
		return ;
	ws += AST_COUNT;
	ast_debug(root->right, ws);
	ft_printf("\n");
	for (int i = AST_COUNT; i < ws; i++)
		ft_printf(" ");
	ft_printf("[%s][%d]\n", root->token->data, root->type);
	// if (root->token->next)
	// 	ft_printf("[%s]", root->token->next->data);
	// if (root->token->next->next)
	// 	ft_printf("[%s]", root->token->next->next->data);
	ast_debug(root->left, ws);
}

// void	parser_debug(t_ast *ast)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	ft_putstr_fd(tgoto(CM, 40, 0), 0);
// 	tputs(CE, 1, print_char);
// 	while (ast)
// 	{
// 		ft_putstr_fd(tgoto(CM, 40, i), 0);
// 		while (ast->cmd_start != ast->cmd_end)
// 		{
// 			ft_printf("\targ no. %d: [%s]", j, ast->cmd_start[j]);
// 			j++;
// 		}
// 		ast = ast->next;
// 		i++;
// 	}
// 	ft_printf("\033[u");	
// }

void	lexer_debug(t_lexer *lexer)
{
	int	i;

	i = 2;
	ft_putstr_fd(tgoto(CM, 80, 0), 0);
	tputs(CE, 1, print_char);
	ft_printf("%s: [%d]", "token count", lexer->count);
	ft_putstr_fd(tgoto(CM, 80, 1), 0);
	tputs(CE, 1, print_char);
	ft_printf("flags: ");
	ft_print_bits(lexer->flags, 16);
	ft_putstr_fd(tgoto(CM, 80, 2), 0);
	tputs(CE, 1, print_char);
	while (lexer->head)
	{
		ft_putstr_fd(tgoto(CM, 80, i), 0);
		ft_printf("%s: [%s]", "token", lexer->head->data);
		if (lexer->head == lexer->last)
			break ;
		lexer->head = lexer->head->next;
		i++;
	}
	ft_printf("\033[u");
}

void	print_debug(t_shell *sh)
{
	ft_printf("\033[s");
	ft_printf("\033[1;1f %10s: [%3d]\033[u", "CURSOR X", sh->x);
	ft_printf("\033[2;1f %10s: [%3d]\033[u", "INDEX", sh->i);
	ft_printf("\033[3;1f %10s: [%3d]\033[u", "KEY", sh->key);
	ft_printf("\033[4;1f %10s: [%3d]\033[u", "LEN", sh->len);
	ft_printf("\033[5;1f %10s: [%-70s]\033[u", "INPUT", sh->input);
	// t_hist *hist = sh->hist
	ft_printf("\033[6;1f %10s: [%3d, %3d]\033[u", "HIST", sh->hist_i, sh->hist_count);
	ft_printf("\033[u");
}
