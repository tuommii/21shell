/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:44:25 by srouhe            #+#    #+#             */
/*   Updated: 2020/07/12 15:18:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Fork new child process and execute normal commands
*/

static int		fork21(char *path, char **args)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) == -1)
		exit_error(FORK_ERR, STR_FORK_ERR);
	listen_signals();
	if (!pid)
	{
		if ((status = execve(path, args, g_sh.env)) == -1)
			exit_error(EXECVE_ERROR, STR_EXECVE_ERR);
	}
	else
		wait(&status);
	free(path);
	return (exec_status(status));
}

/*
** Check binary execution rights and execve type ( pipe | normal )
*/

static int		check_binary(char *path, char **args, struct stat attr, \
							int exec_type)
{
	if (attr.st_mode & S_IFREG)
	{
		if (attr.st_mode & S_IXUSR && exec_type == NORMAL_EXEC)
			return (fork21(path, args));
		else if (attr.st_mode & S_IXUSR && exec_type == PIPE_EXEC)
			return (pipe21(path, args));
		else
		{
			print_error(PERMISSION_ERR, path);
			free(path);
		}
		return (EXEC_OK);
	}
	else if (S_ISDIR(attr.st_mode))
		print_error(EISDIR, path);
	free(path);
	return (EXEC_ERROR);
}

/*
** Check for binary in PATH env variable
** Return error if not found
*/

static int		binaries(char **cmd, int exec_type)
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
		if (!lstat(exec, &attr) && \
			!(!ft_strcmp(cmd[0], ".") || !ft_strcmp(cmd[0], "..")))
		{
			ft_freestrarr(path);
			return (check_binary(exec, cmd, attr, exec_type));
		}
		free(exec);
		i++;
	}
	ft_freestrarr(path);
	return (EXEC_ERROR);
}

/*
** Preprocess before execution (fd's | redirection)
*/

int				exec_preprocess(int save[3], t_ast *ast)
{
	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	save[2] = dup(STDERR_FILENO);
	if (init_redirection(ast) != EXEC_OK)
	{
		restore_fd(ast, save);
		return (EXEC_ERROR);
	}
	return (EXEC_OK);
}

/*
** Start execution of a command
*/

int				execute_command(t_ast *ast, int exec_type)
{
	int				r;
	int				save[3];
	char			**cmd;
	struct stat		attr;

	if ((r = exec_preprocess(save, ast)) == EXEC_ERROR)
		return (r);
	if ((cmd = tokens_to_tab(ast)))
	{
		if (is_builtin(cmd[0]))
			r = exec_builtin(cmd);
		else if ((r = binaries(cmd, exec_type) != EXEC_ERROR))
			r = EXEC_OK;
		else if (!lstat(cmd[0], &attr) && ft_strchr(cmd[0], '/'))
			r = check_binary(ft_strdup(cmd[0]), cmd, attr, exec_type);
		else
			r = exec_errors(cmd[0]);
		ft_freestrarr(cmd);
	}
	restore_fd(ast, save);
	return (r);
}
