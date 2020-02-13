/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 18:13:41 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 16:29:19 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		unset_env(int pos)
{
	int		i;

	ft_strdel(&g_sh.env[pos]);
	i = pos;
	while (g_sh.env[i + 1])
	{
		g_sh.env[i] = ft_strdup(g_sh.env[i + 1]);
		free(g_sh.env[i + 1]);
		i++;
	}
	g_sh.env[i] = NULL;
}

/*
**		Built in unsetenv command.
**		One or multiple arguments.
**		Persist deleted env for later recovery.
*/

int				unsetenv_builtin(char **args)
{
	int		i;
	int		pos;

	i = 0;
	if (!args[0])
		ft_putendl("unsetenv: too few arguments.");
	else
	{
		while (args[i])
		{
			pos = find_env(args[i]);
			if (g_sh.env[pos])
				unset_env(pos);
			i++;
		}
	}
	return (EXEC_OK);
}
