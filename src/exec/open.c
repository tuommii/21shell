/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 14:50:48 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/07 16:15:04 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Open file based on redirection type: append (>>), read (<), trunc (>)
*/

int	open_file(t_token *token)
{
	errno = 0;
	if (token->type & T_DRARR)
	{
		if ((token->fd = open(token->next->data, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
			print_error(errno, token->next->data);
	}
	else if (token->type & T_SLARR)
	{
		if ((token->fd = open(token->next->data, O_RDONLY)) == -1)
			print_error(errno, token->next->data);
	}
	else
	{
		if ((token->fd = open(token->next->data, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
			print_error(errno, token->next->data);
	}
	if (errno == 0)
		return (EXEC_OK);
	else
		return (EXEC_ERROR);
}