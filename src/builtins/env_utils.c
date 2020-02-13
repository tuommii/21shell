/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:56:31 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 15:28:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		display_env(void)
{
	int		i;

	i = 0;
	while (g_env[i])
	{
		ft_putendl(g_env[i]);
		i++;
	}
	return (1);
}

int		find_env(char *var)
{
	int		i;
	char	*parsed;

	i = 0;
	while (g_env[i])
	{
		parsed = ft_strsub(g_env[i], 0, ft_lfind(g_env[i], '='));
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

char	*get_env(char *var)
{
	int		i;
	char	*parsed;

	i = 0;
	while (g_env[i])
	{
		parsed = ft_strsub(g_env[i], 0, ft_lfind(g_env[i], '='));
		if (ft_strequ(parsed, var))
		{
			free(parsed);
			return (ft_strchr(g_env[i], '=') + 1);
		}
		free(parsed);
		i++;
	}
	return (NULL);
}

char	**realloc_arr(size_t size)
{
	int		i;
	char	**new;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		exit_shell(2);
	while (g_env[i] && i < (int)(size - 1))
	{
		if (!(new[i] = ft_strdup(g_env[i])))
			exit_shell(2);
		free(g_env[i]);
		i++;
	}
	new[size] = NULL;
	free(g_env);
	g_env = NULL;
	return (new);
}
