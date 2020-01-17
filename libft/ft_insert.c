/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:04:29 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/17 07:05:42 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_insert(char *str, int pos, char c)
{
	int i;
	int len;

	len = ft_strlen(str) - 1;
	if (!str || pos < 1 || pos > len + 1)
		return ;
	if (!c)
	{
		i = pos - 1;
		while (i < len)
		{
			str[i] = str[i + 1];
			i++;
		}
		str[len] = '\0';
		return ;
	}
	i = len;
	while (i >= pos - 1)
	{
		str[i + 1] = str[i];
		i--;
	}
	str[pos - 1] = c;
}
