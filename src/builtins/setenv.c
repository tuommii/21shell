/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:01:10 by srouhe            #+#    #+#             */
/*   Updated: 2020/07/12 16:07:30 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*parse_quotes(char *s)
{
	char	quote[2];

	quote[0] = '"';
	quote[1] = '\0';
	return (ft_strreplace(ft_strdup(s), quote, ""));
}

void	set_env(char *key, char *value)
{
	int		i;
	char	*tmp;

	if (!g_sh.env)
		return ;
	tmp = ft_strjoin(key, "=");
	i = find_env(key);
	if (g_sh.env[i])
	{
		ft_strdel(&g_sh.env[i]);
		if (value)
			g_sh.env[i] = ft_strjoin(tmp, value);
		else
			g_sh.env[i] = ft_strdup(tmp);
	}
	else
	{
		g_sh.env = realloc_arr(i + 1);
		if (value)
			g_sh.env[i] = ft_strjoin(tmp, value);
		else
			g_sh.env[i] = ft_strdup(tmp);
	}
	free(tmp);
}

/*
**		Built in setenv command.
**		Arguments: KEY VALUE.
**		If no arguments, display current env variables.
*/

int		setenv_builtin(char **args)
{
	char	*tmp;

	if (!args[0])
		display_env();
	else if (args[1] && args[2])
	{
		ft_putendl("setenv: too many arguments.");
		return (EXEC_ERROR);
	}
	else if (args[1])
	{
		tmp = parse_quotes(args[1]);
		set_env(args[0], tmp);
		free(tmp);
	}
	else
		set_env(args[0], args[1]);
	return (EXEC_OK);
}
