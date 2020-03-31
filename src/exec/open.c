/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 14:50:48 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 14:51:03 by srouhe           ###   ########.fr       */
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
			return (print_error(errno, token->next->data));
	}
	else if (token->type & T_SLARR)
	{
		if ((token->fd = open(token->next->data, O_RDONLY)) == -1)
			return (print_error(errno, token->next->data));
	}
	else
	{
		if ((token->fd = open(token->next->data, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
			return (print_error(errno, token->next->data));
	}
	// ft_printf("Success opening [%s]\n", token->next->data);
	return (EXIT_SUCCESS);
}