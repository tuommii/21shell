/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:05:03 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/11 09:30:48 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinch(char const *s1, char c)
{
	char	*dest;
	int		i;
	int		len;

	if (!s1 || !c)
		return (NULL);
	len = ft_strlen(s1);
	dest = ft_strnew(len + 1);
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		*(dest + i) = *(s1 + i);
	*(dest + i) = c;
	*(dest + i + 1) = '\0';
	return (dest);
}
