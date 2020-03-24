/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:23:14 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/24 16:44:28 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	open_file(t_token *token)
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
	else if (token->type & T_SRARR)
	{
		if ((token->fd = open(token->next->data, O_WRONLY | O_CREAT | O_TRUNC | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (EXEC_ERROR);
	}
	return (EXIT_SUCCESS);
}

static int	redirect(t_token *token)
{
	// Check for IO numbers here first and dup2(token->fd, IO)
	// ft_printf("KRAA BITCH [%d]\n", token->fd);
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