/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:23:14 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/13 19:38:17 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	redirect(t_token *token)
{
	if (token->prev && token->prev->type & IO_NUM)
		return (dup21(token->fd, ft_atoi(token->prev->data), \
						token->next->data));
	else if (token->type & T_SLARR)
		return (dup21(token->fd, STDIN_FILENO, token->next->data));
	else
		return (dup21(token->fd, STDOUT_FILENO, token->next->data));
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
		return (dup21(ft_atoi(token->next->data), src, token->next->data));
	else if (token->next->type & T_DASH)
		close(src);
	else if (token->next->type & T_FILE)
	{
		if (open_file(token) == EXEC_ERROR)
			return (EXEC_ERROR);
		return (dup21(token->fd, src, token->next->data));
	}
	else
	{
		print_error(AMB_REDIR_ERR, token->next->data);
		return (EXEC_ERROR);
	}
	return (EXEC_OK);
}

/*
** Iterate tokens for one command, looking for redirections
** Aggregate fd's if >& or <& etc.
** Open a file and redirect if >>, >, <
*/

int			init_redirection(t_ast *ast)
{
	t_token	*tmp;

	tmp = ast->token;
	while (tmp)
	{
		if (tmp->type & T_LESS_AND || tmp->type & T_GREAT_AND)
		{
			if (aggregate_fds(tmp) == EXEC_ERROR)
				return (EXEC_ERROR);
			tmp = tmp->next;
		}
		else if (tmp->type & MASK_REDIR)
		{
			if (open_file(tmp) == EXEC_ERROR)
				return (EXEC_ERROR);
			if (redirect(tmp) == EXEC_ERROR)
				return (EXEC_ERROR);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
		if (tmp == ast->cmd_end)
			break ;
	}
	return (EXEC_OK);
}
