/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:52:47 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/21 21:04:45 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(void)
{
	if (!re_match("^exa.*json$", "example_filename.json"))
		ft_putendl("RE ERROR");
	ft_printf("%d and a truncated %.4s\n", 123, "test string");
	return (0);
}