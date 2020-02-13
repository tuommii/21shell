/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:44:25 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 17:18:06 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		fork21(char *path, char **args)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if ((execve(path, args, NULL)) == -1)
			exit_error(EXECVE_ERROR);
	}
	else if (pid < 0)
	{
		ft_putendl("21sh: failed to create child process.");
		exit_error(FORK_ERROR);
	}
	wait(&pid);
	return (EXEC_OK);
}

static int		check_binary(char *path, char **args, struct stat attr)
{
	if (attr.st_mode & S_IFREG)
	{
		if (attr.st_mode & S_IXUSR)
			return (fork21(path, args));
		else
		{
			ft_putstr("21sh: permission denied: ");
			ft_putendl(path);
			free(path);
		}
		return (EXEC_OK);
	}
	return (EXEC_ERROR);
}

static int		binaries(char **cmd)
{
	int				i;
	char			**path;
	char			*exec;
	struct stat		attr;

	i = 0;
	path = ft_strsplit(get_env("PATH"), ':');
	while (path && path[i])
	{
		exec = ft_pathjoin(path[i], cmd[0]);
		if (!lstat(exec, &attr))
		{
			ft_freestrarr(path);
			return (check_binary(exec, cmd, attr));
		}
		free(exec);
		i++;
	}
	ft_freestrarr(path);
	return (EXEC_ERROR);
}

int				execute_command(t_ast *ast)
{
	int		r;
	char	**cmd;

	if ((cmd = expand_tokens(ast)))
	{
		if ((builtins(cmd) == EXEC_OK))
			r = EXEC_OK;
		else if ((binaries(cmd) == EXEC_OK))
			r = EXEC_OK;
	}
	array_debug(cmd);
	ft_freestrarr(cmd);
	return (EXEC_OK);
}
