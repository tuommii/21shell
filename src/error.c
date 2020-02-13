/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:57:57 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 18:47:10 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// free mem also
void	exit_error(int errno)
{
	errno == MALLOC_ERROR ? ft_putendl("21sh: malloc error.") : PASS;
	errno == FORK_ERR ? ft_putendl("21sh: failed to create child process.") : PASS;
	errno == EXECVE_ERROR ? ft_putendl("21sh: execve error.") : PASS;
	reset_shell();
	ft_freestrarr(g_sh.env);
	exit(errno);
}

void	print_error(int errno, char *msg)
{
	g_sh.y++;
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, g_sh.y), OUTPUT);
	errno == SYNTAX_ERR ? ft_printf("21sh: syntax error near unexpected token `%s'", msg) : PASS;
	errno == PERMISSION_ERR ? ft_printf("21sh: permission denied: %s", msg) : PASS;
}
