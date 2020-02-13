/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:12:05 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 16:29:03 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**		Builtin echo command.
*/

int				echo_builtin(char **args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!args[i])
	{
		ft_putchar('\n');
		return (EXEC_OK);
	}
	if (ft_strequ(args[i], "-n"))
		flag = 1;
	i += flag;
	while (args[i])
	{
		ft_putstr(args[i]);
		i++;
		if (args[i])
			ft_putchar(' ');
	}
	if (!flag)
		ft_putchar('\n');
	return (EXEC_OK);
}
