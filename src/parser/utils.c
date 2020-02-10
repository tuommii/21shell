/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:34:01 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/10 14:06:45 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		args_count(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type & T_STR)
	{
		i++;
		token = token->next;
	}
	return (i);
}

int		get_next_operator(t_lexer **lexer)
{
	(void)lexer;
	return (0);
}
