/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:56:31 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 20:44:25 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		display_env(void)
{
	int		i;

	i = 0;
	while (g_sh.env[i])
	{
		ft_putendl(g_sh.env[i]);
		i++;
	}
	return (EXEC_OK);
}

int		find_env(char *var)
{
	int		i;
	char	*parsed;

	i = 0;
	while (g_sh.env[i])
	{
		parsed = ft_strsub(g_sh.env[i], 0, ft_lfind(g_sh.env[i], '='));
		if (ft_strequ(parsed, var))
		{
			free(parsed);
			return (i);
		}
		free(parsed);
		i++;
	}
	return (i);
}

char	**realloc_arr(size_t size)
{
	int		i;
	char	**new;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (g_sh.env[i] && i < (int)(size - 1))
	{
		if (!(new[i] = ft_strdup(g_sh.env[i])))
			return (NULL);
		free(g_sh.env[i]);
		i++;
	}
	new[size] = NULL;
	free(g_sh.env);
	g_sh.env = NULL;
	return (new);
}
