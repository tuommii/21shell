/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:44:25 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 15:41:02 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "exec.h"

static int		fork21(char *path, char **args)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		execve(path, args, NULL);
	else if (pid < 0)
	{
		ft_putendl("21sh: failed to create child process.");
		return (-1);
	}
	wait(&pid);
	return (1);
}

int				execute_command(t_ast *ast, t_shell *sh)
{
	int		r;
	char	**cmd;

	if ((cmd = expand_tokens(ast)))
	{
		// if ((builtins(cmd, sh) == 1))
		// 	return (EXEC_OK);
		// r = fork21(cmd[0], cmd);
	}
	array_debug(cmd);
	ft_freestrarr(cmd);
	return (r);
}
