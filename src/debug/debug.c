/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:58:45 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/05 15:23:27 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_debug(t_lexer *lexer)
{
	int	i;

	i = 2;
	ft_putstr_fd(tgoto(CM, 40, 0), 0);
	tputs(CE, 1, print_char);
	ft_printf("%20s: [%d]", "token count", lexer->count);
	ft_putstr_fd(tgoto(CM, 40, 1), 0);
	tputs(CE, 1, print_char);
	ft_print_bits(lexer->flags, 16);
	ft_putstr_fd(tgoto(CM, 40, 2), 0);
	tputs(CE, 1, print_char);
	while (lexer->head)
	{
		ft_putstr_fd(tgoto(CM, 40, i), 0);
		ft_printf("%20s: [%s]", "token", lexer->head->data);
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
