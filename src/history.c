/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:35:40 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/18 09:16:41 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Should we write history to file so its permanent
// Search autocompletions after tabpress

/*
`cl'
String of commands to clear the entire screen and position the cursor at the upper left corner.
`cd'
String of commands to clear the line the cursor is on, and all the lines below it, down to the bottom of the screen. This command string should be used only with the cursor in column zero; their effect is undefined if the cursor is elsewhere.
`ce'
String of commands to clear from the cursor to the end of the current line.
`ec'
String of commands to clear n characters, starting with the character that the cursor is on. This command string is expected to leave the cursor position unchanged. The parameter n should never be large enough to reach past the right margin; the effect of such a large parameter would be undefined.
*/
#include "shell.h"


static int is_empty(char *str)
{
	if (!str || !str[0])
		return (1);
	return (0);
}

void free_hist_item(t_hist **hist)
{
	if (hist && *hist)
	{
		ft_strdel(&(*hist)->str);
		free(*hist);
		*hist = NULL;
	}
}

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

// NULL to head creates new node as head
void hist_append(t_hist **head, char *str)
{
	t_hist *new;
	t_hist *curr;

	curr = *head;
	if (!(new = new_hist_item(str)))
	{
		// TODO: Use global exit func or dont close app
		// ft_printf("History item failed\n");
		return ;
		// exit(0);
	}

	if (*head == NULL)
	{
		*head = new;
		return ;
	}

	new->i++;
	while (curr->next != NULL)
	{
		new->i++;
		curr = curr->next;
	}
	curr->next = new;
	new->prev = curr;
	(*head)->prev = new;
}

void hist_print(t_hist *node)
{
	while (node != NULL)
	{
		ft_printf("[%2d] HIST: [%s]\n", node->i, node->str);
		node = node->next;
	}
}
