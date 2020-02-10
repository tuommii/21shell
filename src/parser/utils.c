/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:34:01 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/10 18:53:57 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// //deprecated
// int		args_count(t_token *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token && token->type & T_STR)
// 	{
// 		i++;
// 		token = token->next;
// 	}
// 	return (i);
// }

int		next_operator(t_token *token, int type)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type & type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
