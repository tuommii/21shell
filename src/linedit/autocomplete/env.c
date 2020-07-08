/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:03:03 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/08 14:44:26 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static int get_envname_last_index(char *str)
{
	char *cpy = str;
	int i = 0;
	while (cpy[i] && cpy[i] != '=')
		i++;
	return (i);
}

static int count_envs(char **envs)
{
	char	**temp;
	int		i;

	temp = envs;
	i = 0;
	while (*temp)
	{
		temp++;
		i++;
	}
	return (i);
}

void load_envs(t_completer *ac, char **envs)
{
	char **cpy;
	int i;

	ac->envs_count = count_envs(envs);
	ac->envs = malloc(sizeof(char *) * ac->envs_count);
	i = 0;
	while (i < ac->envs_count)
	{
		int last = get_envname_last_index(envs[i]);
		// if (!last)
		// 	last = 1;
		ac->envs[i] = malloc(sizeof(char) * last + 1);
		ft_strncpy(ac->envs[i], envs[i], last);
		ac->envs[i][last] = '\0';
		//ft_printf("\n%d\n", i);
		i++;
		// ft_printf("\nalive\n");
	}
	ac->envs[i] = NULL;
}

static int	ft_env_exists(char *name, char *given, int len_given)
{
	if (ft_strncmp(name, given, len_given) == 0 \
	&& name[len_given] && name[len_given] == '=')
		return (1);
	return (0);
}

char		*ft_getenv(char *name, char **envs)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(name);
	if (!name || ft_strequ(name, "$"))
		return (NULL);
	while (envs[i])
	{
		if (ft_env_exists(envs[i], name, len))
			return (&envs[i][len + 1]);
		i++;
	}
	return (NULL);
}
