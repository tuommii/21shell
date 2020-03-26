/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:12:05 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/26 11:43:00 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**		Builtin echo command.
*/

int				echo_builtin(char **args)
{
	int		i;

	i = 0;
	// g_sh.y++;
	// ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, g_sh.y), OUTPUT);
	if (!args[i])
	{
		ft_putchar('\n');
		return (EXEC_OK);
	}
	while (args[i])
	{
		ft_putstr(args[i]);
		i++;
		if (args[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (EXEC_OK);
}
