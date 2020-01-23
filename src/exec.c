/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:08 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/19 16:27:12 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		run_cmd(char *path, char **args)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, signal_handler);
	if (!pid)
		execve(path, args, g_env);
	else if (pid < 0)
	{
		ft_putendl("21sh: failed to create child process.");
		return (-1);
	}
	wait(&pid);
	free(path);
	return (1);
}

static int		check_binary(char *path, char **args, struct stat attr)
{
	if (attr.st_mode & S_IFREG)
	{
		if (attr.st_mode & S_IXUSR)
			return (run_cmd(path, args));
		else
		{
			ft_putstr("minishell: permission denied: ");
			ft_putendl(path);
		}
		return (1);
	}
	return (0);
}

static int		bins(char **cmd)
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
	return (0);
}

static int		builtins(char **cmd)
{
	if (ft_strequ(cmd[0], "exit"))
		return (-1);
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
	return (0);
}

/*
**		Executes commands in minishell.
**			1. Check for built in commands.
**			2. Check if exit command.
**			3. Check for system binaries.
**			4. Check for binaries in PWD.
*/

int				exec_cmd(char **cmd)
{
	int				r;
	struct stat		attr;

	if ((r = builtins(cmd)) == 1)
		return (0);
	else if (r == -1)
		return (-1);
	else if (bins(cmd) == 1)
		return (0);
	else if (!lstat(cmd[0], &attr))
		return (check_binary(ft_strdup(cmd[0]), cmd, attr));
	ft_putstr("21sh: command not found: ");
	ft_putendl(cmd[0]);
	return (0);
}
