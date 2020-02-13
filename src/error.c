/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:57:57 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 22:35:46 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// free mem also
void	exit_error(int errno)
{
	g_sh.y++;
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, g_sh.y), OUTPUT);
	errno == MALLOC_ERROR ? ft_putendl("21sh: malloc error.") : PASS;
	errno == FORK_ERR ? ft_putendl("21sh: failed to create child process.") : PASS;
	errno == EXECVE_ERROR ? ft_putendl("21sh: execve error.") : PASS;
	errno == DUP_ERR ? ft_putendl("21sh: dup error.") : PASS;
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
	errno == NOT_FOUND_ERR ? ft_printf("21sh: no such file or directory: %s", msg) : PASS;
	errno == NOT_DIR_ERR ? ft_printf("21sh: not a directory: %s", msg): PASS;
}
