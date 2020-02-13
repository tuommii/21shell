/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:08:50 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 22:36:42 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		// exit(ft_launch_one_side(node_left));
	}
	// else
	// {
	// 	status_right = ft_pipe_to_right(fd, node_right);
	// 	close(fd[0]);
	// 	waitpid(pid_left, NULL, 0);
	// }
	return (EXEC_OK);
}