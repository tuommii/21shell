/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:44:25 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/24 15:12:56 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		open_file(t_token *token)
{
	if (token->type & T_DRARR)
	{
		if ((token->fd = open(token->next->data, O_WRONLY | O_CREAT | O_APPEND | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (EXEC_ERROR);
	}
	else if (token->type & T_SLARR)
	{
		if ((token->fd = open(token->next->data, O_RDONLY)) == -1)
			return (EXEC_ERROR);
	}
	else
	{
		if ((token->fd = open(token->next->data, O_WRONLY | O_CREAT | O_TRUNC | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (EXEC_ERROR);
	}
	return (EXIT_SUCCESS);
}

static int	redirect(t_token *token)
{
	if (token->type & T_SLARR)
		return (dup2(token->fd, STDIN_FILENO));
	else
		return (dup2(token->fd, STDOUT_FILENO));
}

int			init_redirection(t_ast *ast)
{
	t_token	*tmp;

	tmp = ast->token;
	while (tmp)
	{
		if (tmp->type & MASK_REDIR)
		{
			if (open_file(tmp) == EXEC_ERROR)
				return (EXEC_ERROR);
			if (redirect(tmp) == EXEC_ERROR)
				return (EXEC_ERROR);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	return (EXEC_OK);
}

int		exec_preprocess(int save[3], t_ast *ast)
{
	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	save[2] = dup(STDERR_FILENO);
	if (init_redirection(ast) != EXEC_OK)
	{
		restore_fd(ast, save);
		return (EXEC_ERROR);
	}
	return (EXIT_SUCCESS);
}

/*
** Fork new child process and execute
*/

static int		fork21(char *path, char **args)
{
	pid_t	pid;

	pid = fork();
	// signal(SIGINT, signal_handler);
	if (!pid)
	{
		if ((execve(path, args, g_sh.env)) == -1)
			exit_error(EXECVE_ERROR);
	}
	else if (pid < 0)
		exit_error(FORK_ERR);
	wait(&pid);
	return (EXEC_OK);
}

/*
** Check binary execution rights
*/

static int		check_binary(char *path, char **args, struct stat attr)
{
	if (attr.st_mode & S_IFREG)
	{
		if (attr.st_mode & S_IXUSR)
			return (fork21(path, args));
		else
		{
			print_error(PERMISSION_ERR, path);
			free(path);
		}
		return (EXEC_OK);
	}
	return (EXEC_ERROR);
}

/*
** Check for binary in PATH env variable
** Return error if not found
*/

static int		binaries(char **cmd)
{
	int				i;
	char			**path;
	char			*exec;
	struct stat		attr;

	i = 0;
	path = ft_strsplit(getenv("PATH"), ':');
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
	int		save[3];
	char	**cmd;

	if ((r = exec_preprocess(save, ast)) == REDIR_ERR)
		return (r);
	if ((cmd = expand_tokens(ast)))
	{
		if ((builtins(cmd) == EXEC_OK))
			r = EXEC_OK;
		else if ((binaries(cmd) == EXEC_OK))
			r = EXEC_OK;
	}
	ft_freestrarr(cmd);
	return (EXEC_OK);
}
