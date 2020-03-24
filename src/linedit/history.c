/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:23:16 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/14 11:27:39 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static t_hist *new_hist_item(char *str)
{
	t_hist *new;
	if (is_empty(str))
		return (NULL);
	if (!(new = ft_memalloc(sizeof(t_hist))))
	{
		// TODO: Use global exit func or dont close app
		ft_printf("History item failed\n");
		return (NULL);
		// exit(0);
	}
	new->str = ft_strdup(str);
	new->prev = new;
	new->next = NULL;
	new->i = 0;
	return (new);
}

static void check_count(t_hist **head, t_hist *new)
{
	t_hist *delete;
	if (new->i >= MAX_HISTORY)
	{
		delete = *head;
		(*head) = (*head)->next;
		ft_strdel(&delete->str);
		free(delete);
		delete = NULL;
	}
}

static void traverse_end(t_hist **curr, t_hist *new)
{
	new->i++;
	while ((*curr)->next != NULL)
	{
		new->i++;
		*curr = (*curr)->next;
	}
}

// NULL to head creates new node as head
int hist_append(t_hist **head, char *str)
{
	t_hist *new;
	t_hist *curr;

	curr = *head;
	// TODO: Use global exit func or dont close app
	if (!(new = new_hist_item(str)))
		return (0);
	if (*head == NULL)
	{
		*head = new;
		return (1);
	}
	traverse_end(&curr, new);
	if (!ft_strcmp(str, curr->str))
	{
		free(new->str);
		free(new);
		return (0);
	}
	curr->next = new;
	new->prev = curr;
	check_count(head, new);
	(*head)->prev = new;
	return (1);
}

t_hist *hist_pop(t_hist **head, int index)
{
	t_hist *node;

	if (!(node = (*head)->prev))
		return (NULL);
	if (!index)
		return (node);
	else
	{
		while (index-- > 0 && node)
		{
			node = node->prev;
		}
	}
	return (node);
}
