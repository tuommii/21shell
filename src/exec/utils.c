/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:03:38 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/03 12:43:55 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Check if provided command is a built in cmd
*/

int		builtins(char **cmd)
{
	if (ft_strequ(cmd[0], "exit"))
		ft_printf("to-do: Implement exit.");
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

/*
** Expand list of tokens into **command
*/

char	**expand_tokens(t_ast *ast)
{
	int		i;
	char	**cmd;

	if (!(cmd = (char **)malloc(sizeof(char *) * (ast->nbr_token + 1))))
		exit_error(MALLOC_ERROR);
	i = 0;
	while (ast->token != ast->cmd_end)
	{
		if (ast->token->type & MASK_REDIR)
			ast->token = ast->token->next->next;
		else
		{
			cmd[i] = ft_strdup(ast->token->data);
			ast->token = ast->token->next;
			i++;			
		}
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
	if (!ast)
		return ;
	tmp = ast->token;
	while (tmp)
	{
		if (tmp->type & MASK_REDIR)
		{
			if (tmp->fd > 0)
				close(tmp->fd);
		}
		tmp = tmp->next;
	}
}
