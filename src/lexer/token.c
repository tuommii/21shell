/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:10:05 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/04 22:49:10 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(char *data)
{
	t_token		*new;
	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	new->data = ft_strdup(data);
	new->next = NULL;
}

int		add_token(t_lexer *lexer, char *data)
{
	// add new token to lexer and update info, keep track of head and last
	t_token	*token;
	t_token	*tmp;

	ft_printf("                        adding new token with: %s\n", data);
	token = new_token(data);
	if (!lexer->head)
		lexer->head = token;
	else
	{
		tmp = lexer->head;
		while (tmp)
			tmp = tmp->next;
		tmp = token;
	}
	lexer->count++;
	return (ft_strlen(data));
}