/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:41:10 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/14 16:42:58 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelat(t_list **lst, int index, void (*del)(void*, size_t))
{
	t_list	*node;
	t_list	*prev;
	int		i;

	if ((node = *lst) == NULL)
		return ;
	prev = NULL;
	i = 0;
	while (node)
	{
		if (i == index)
		{
			if (prev)
				prev->next = node->next;
			else
				*lst = node->next;
			del(node->content, node->content_size);
			return ;
		}
		prev = node;
		node = node->next;
		i++;
	}
}
