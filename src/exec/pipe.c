/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:08:50 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/24 15:22:38 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	pipe_to_right(int fd[2], t_ast *node_right)
{
	pid_t	pid_right;
	int		status_right;

	if ((pid_right = fork()) == -1)
		exit_error(FORK_ERR);
	if (!pid_right)
	{
		close(fd[1]);
		if ((dup2(fd[0], STDIN_FILENO)) == -1)
			exit_error(DUP_ERR);
		if (node_right->parent->parent && node_right->parent->parent->type & T_PIPE)
			exit(init_pipeline(node_right, node_right->parent->parent->right));
		else
			exit(execute_command(node_right));
	}
	else
	{
		close(fd[1]);
		waitpid(pid_right, &status_right, 0);
	}
	return (status_right);
}

int			init_pipeline(t_ast *left, t_ast *right)
{
	int		fd[2];
	int		status_right;
	pid_t	pid_left;

	if (pipe(fd) == -1)
		exit_error(PIPE_ERR);
	else if ((pid_left = fork()) == -1)
		exit_error(FORK_ERR);
	if (!pid_left)
	{
		close(fd[0]);
		if ((dup2(fd[1], STDOUT_FILENO)) == -1)
			exit_error(DUP_ERR);
		execute_command(left);
	}
	else
	{
		status_right = pipe_to_right(fd, right);
		close(fd[0]);
		waitpid(pid_left, NULL, 0);
	}
	return (EXEC_OK);
}
