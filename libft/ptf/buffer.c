/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:45:21 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/21 20:45:42 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Buffer management functions replicating real printf.
** Fill the buffer with dynamically allocated tmp string. If full, flush it.
** Clear and free tmp string and reset struct values.
*/

void				flush_buffer(t_ptf **p)
{
	write((*p)->fd, (*p)->buf, (*p)->buf_index);
	ft_bzero((*p)->buf, BUF_SIZE);
	(*p)->buf_index = 0;
}

void				fill_buffer(t_ptf **p)
{
	int	i;

	i = 0;
	if (!(*p)->tmp)
		return ;
	while ((*p)->tmp[i])
	{
		(*p)->buf[(*p)->buf_index++] = (*p)->tmp[i++];
		(*p)->len++;
		if ((*p)->buf_index == BUF_SIZE || (*p)->buf[(*p)->buf_index] == '\n')
			flush_buffer(p);
	}
	if ((*p)->tmp)
	{
		free((*p)->tmp);
		(*p)->tmp = NULL;
	}
	(*p)->width = 0;
	(*p)->flags = 0;
	(*p)->prec = 0;
	(*p)->tmplen = 0;
	(*p)->padc = ' ';
}