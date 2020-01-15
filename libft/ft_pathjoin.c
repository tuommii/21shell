/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:03:59 by mtuomine          #+#    #+#             */
/*   Updated: 2019/12/11 10:10:36 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathjoin(char *a, char *b)
{
	char *temp;
	char *res;

	if (a == NULL)
	{
		if (b == NULL)
			return (ft_strnew(1));
		return (ft_strdup(b));
	}
	if (b == NULL)
		return (ft_strdup(a));
	temp = NULL;
	res = NULL;
	if (!ft_endswith(a, "/"))
	{
		temp = ft_strjoinch(a, '/');
		res = ft_strjoin(temp, b);
		ft_strdel(&temp);
		return (res);
	}
	return (ft_strjoin(a, b));
}
