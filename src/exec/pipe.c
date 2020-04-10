/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:08:50 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/10 13:41:21 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Execute pipe commands (no fork)
*/

int			pipe21(char *path, char **args)
{
	int		status;

	if ((status = execve(path, args, g_sh.env)) == -1)
		exit_error(EXECVE_ERROR);
	return (exec_status(status));
}

/*
** If upper in the tree there's another pipe, recurse back to init pipeline
** Otherwise execute right side of the pipe
*/

static int	pipe_to_right(int fd[2], t_ast *right)
{
	pid_t	pid_right;
	int		status_right;

	status_right = 0;
	if ((pid_right = fork()) == -1)
		exit_error(FORK_ERR);
	if (!pid_right)
	{
		close(fd[1]);
		dup21(fd[0], STDIN_FILENO, right->token->data);
		if (right->parent->parent && right->parent->parent->type & T_PIPE)
		{
			ft_printf("recurse further, exec [%s], go to [%s]\n", right->token->data, right->parent->parent->right);
			exit(execute_pipeline(right, right->parent->parent->right));
		}
		else
		{
			ft_printf("pipe_to_right, exec [%s], from [%s]\n", right->token->data, right->parent->left->token->data);
			exit(execute_command(right, PIPE_EXEC));
		}
	}
	else
	{
		close(fd[1]);
		waitpid(pid_right, &status_right, 0);
	}
	return (exec_status(status_right));
}

/*
** Initialize pipeline
*/

int			execute_pipeline(t_ast *left, t_ast *right)
{
	int		fd[2];
	int		status;
	pid_t	pid_left;

	if (pipe(fd) == -1)
	{
		print_error(PIPE_ERR, left->left->token->data);
		return (EXEC_ERROR);
	}
	else if ((pid_left = fork()) == -1)
		exit_error(FORK_ERR);
	else if (!pid_left)
	{
		close(fd[0]);
		dup21(fd[1], STDOUT_FILENO, left->token->data);
		ft_printf("no pid_left, exec [%s]\n", left->token->data);
		exit(execute_command(left, PIPE_EXEC));
	}
	else
	{
		status = pipe_to_right(fd, right);
		close(fd[0]);
		waitpid(pid_left, NULL, 0);
	}
	return (status);
}
