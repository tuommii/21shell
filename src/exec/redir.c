/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:23:14 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 15:57:10 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	redirect(t_token *token)
{
	if (token->prev && token->prev->type & IO_NUM)
	{
		ft_printf("Redirecting fd [%d] to [%d]\n", ft_atoi(token->prev->data), token->fd);
		return (dup2(token->fd, ft_atoi(token->prev->data)));
	}
	else if (token->type & T_SLARR)
		return (dup2(token->fd, STDIN_FILENO));
	else
	{
		// ft_printf("Redirecting fd [%d] to [%d]\n", STDOUT_FILENO, token->fd);
		return (dup2(token->fd, STDOUT_FILENO));
	}
}

/*
** Aggregate correct fds with >& and <& operators
*/

int			aggregate_fds(t_token *token)
{
	int src;

	if (token->prev && token->prev->type & IO_NUM)
		src = ft_atoi(token->prev->data);
	else if (token->type & T_LESS_AND)
		src = STDIN_FILENO;
	else if (token->type & T_GREAT_AND)
		src = STDOUT_FILENO;
	if (str_isnumeric(token->next->data))
		return (dup2(ft_atoi(token->next->data), src));
	else if (!ft_strcmp(token->next->data, "-"))
		close(src);
	else
		return (print_error(AMB_REDIR_ERR, NULL));
	return (1);
}

/*
** Open a pipe for << heredoc
*/

// int		heredoc(t_token *token)
// {
// 	int fd[2];

// 	if (pipe(fd) == -1)
// 		return (print_error(PIPE_ERR, NULL));
// 	write(fd[1], token->heredoc, ft_strlen(token->heredoc));
// 	close(fd[1]);
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	return (1);
// }

int			init_redirection(t_ast *ast)
{
	t_token	*tmp;

	tmp = ast->token;
	while (tmp)
	{
		if (tmp->type & T_LESS_AND || tmp->type & T_GREAT_AND)
		{
			if (aggregate_fds(tmp) == -1)
				return (EXEC_ERROR);
			tmp = tmp->next->next;
		}
		// else if (tmp->type & T_DLARR)
		// {
		// 	if (heredoc(tmp) == -1)
		// 		return (EXEC_ERROR);
		// 	tmp = tmp->next->next;			
		// }
		else if (tmp->type & MASK_REDIR)
		{
			if (open_file(tmp) == -1)
				return (EXEC_ERROR);
			if (redirect(tmp) == -1)
				return (EXEC_ERROR);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	return (EXEC_OK);
}