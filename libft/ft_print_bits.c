/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:54:45 by srouhe            #+#    #+#             */
/*   Updated: 2020/07/12 10:37:46 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_print_bits(uint64_t bits, int len)
{
	uint64_t		bit;

	while (len--)
	{
		bit = (bits >> len & 1) + '0';
		write(1, &bit, 1);
		if (len % 8 == 0)
			write(1, " ", 1);
	}
}
