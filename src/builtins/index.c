/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:26:06 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/07 15:41:01 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Check if command is in builtins
*/

int		is_builtin(char *cmd)
{
	if (
			ft_strequ(cmd, "exit")
			|| ft_strequ(cmd, "echo")
			|| ft_strequ(cmd, "cd")
			|| ft_strequ(cmd, "setenv")
			|| ft_strequ(cmd, "unsetenv")
			|| ft_strequ(cmd, "env")
		)
		return (1);
	else
		return (0);
}

/*
** Launch builtin command
*/

int		exec_builtin(char **cmd)
{
	if (ft_strequ(cmd[0], "exit"))
		cleanup(g_sh.line);
	else if (ft_strequ(cmd[0], "echo"))
		return (echo_builtin(cmd + 1));
	else if (ft_strequ(cmd[0], "cd"))
		return (cd_builtin(cmd + 1));
	else if (ft_strequ(cmd[0], "setenv"))
		return (setenv_builtin(cmd + 1));
	else if (ft_strequ(cmd[0], "unsetenv"))
		return (unsetenv_builtin(cmd + 1));
	else if (ft_strequ(cmd[0], "env"))
		return (display_env());
	return (EXEC_ERROR);
}