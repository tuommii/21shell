/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:23:14 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/26 17:52:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	open_file(t_token *token)
{
	errno = 0;
	if (token->type & T_DRARR)
	{
		if ((token->fd = open(token->next->data, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
			return (print_error(errno, token->next->data));
	}
	else if (token->type & T_SLARR)
	{
		if ((token->fd = open(token->next->data, O_RDONLY)) == -1)
			return (print_error(errno, token->next->data));
	}
	else if (token->type & T_SRARR)
	{
		if ((token->fd = open(token->next->data, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
			return (print_error(errno, token->next->data));
	}
	// ft_printf("Success opening [%s]\n", token->next->data);
	return (EXIT_SUCCESS);
}

static int	redirect(t_token *token)
{
	errno = 0;
	// Check for IO numbers here first and dup2(token->fd, IO)
	if (token->type & T_SLARR)
		return (dup2(token->fd, STDIN_FILENO));
	else
	{
		// ft_printf("Redirecting fd [%d] to [%d]\n", STDOUT_FILENO, token->fd);
		return (dup2(token->fd, STDOUT_FILENO));
	}
}

int			init_redirection(t_ast *ast)
{
	t_token	*tmp;

	tmp = ast->token;
	while (tmp)
	{
		if (tmp->type & MASK_REDIR)
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