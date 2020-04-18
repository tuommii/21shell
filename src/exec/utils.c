/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:03:38 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/18 13:04:19 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Handle errors while executing dup2
*/

int		dup21(int dst, int src, char *msg)
{
	errno = 0;
	if ((dup2(dst, src)) != -1)
		return (EXEC_OK);
	else
	{
		if (errno == EBADF)
			print_error(BAD_FD_ERR, msg);
		else
			print_error(DUP_ERR, msg);
	}
	return (EXEC_ERROR);
}

/*
** Check child process exit status (normal termination, unhandled signals)
*/

int		exec_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if ((WTERMSIG(status)) == 6)
			ft_putendl_fd("Abort: 6", 2);
		if ((WTERMSIG(status)) == 10)
			ft_putendl_fd("Bus error: 10", 2);
		if ((WTERMSIG(status)) == 11)
			ft_putendl_fd("Segmentation Fault: 11", 2);
		if ((WTERMSIG(status)) == 8)
			ft_putendl_fd("Floating point exception: 8", 2);
		return (WTERMSIG(status) + 128);
	}
	else
		return (EXIT_FAILURE);
}

/*
** Expand list of tokens into **cmd
** Redirection and io number tokens are excluded
** Filenames excluded with `echo`
*/

char	**tokens_to_tab(t_ast *ast)
{
	int		i;
	char	**cmd;

	if (!(cmd = (char **)malloc(sizeof(char *) * (ast->nbr_token + 1))))
		exit_error(MALLOC_ERROR, STR_MALLOC_ERR);
	i = 0;
	while (ast->token)
	{
		if (ast->token->type & MASK_ECHO)
		{
			cmd[i] = ft_strdup(ast->token->data);
			i++;
		}
		ast->token = ast->token->next;
		if (ast->token == ast->cmd_end)
			break ;
	}
	cmd[i] = NULL;
	return (cmd);
}

/*
** Restore normal file descriptors and close opened ones.
*/

void	restore_fd(t_ast *ast, int save[3])
{
	t_token *tmp;

	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	dup2(save[2], STDERR_FILENO);
	close(save[0]);
	close(save[1]);
	close(save[2]);
	tmp = ast ? ast->token : NULL;
	while (tmp)
	{
		if (tmp->fd > 0)
			close(tmp->fd);
		tmp = tmp->next;
	}
}
