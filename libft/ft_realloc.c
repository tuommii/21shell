/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 15:00:33 by srouhe            #+#    #+#             */
/*   Updated: 2020/07/12 10:49:06 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_s, size_t new_s)
{
	void	*new;

	if (!ptr)
		return (NULL);
	if (!(new = ft_memalloc(new_s + 1)))
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new, ptr, old_s < new_s ? old_s : new_s);
	free(ptr);
	return (new);
}
