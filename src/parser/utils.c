/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:34:01 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/07 14:22:07 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Jump to next operator
*/

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

/*
** Remove quoting from input in case of squote or dquote
*/

void	remove_quotes(t_token *token, int wquote)
{
	char	*clean;
	t_token *tmp;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	if (wquote == 34)
		clean = ft_strreplace(tmp->data, "\"", "");
	else if (wquote == 39)
		clean = ft_strreplace(tmp->data, "'", "");
	ft_strdel(&tmp->data);
	tmp->data = clean;
}
