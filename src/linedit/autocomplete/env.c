/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:03:03 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 08:12:41 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

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

int suggestions_env(t_line *line, t_completions **comps)
{
	char **cpy;
	int i;

	if (ft_strcmp((*comps)->ctx, CTX_ENV) != 0)
		return (0);

	(*comps)->count = count_envs(line->envs);
	(*comps)->suggestions = malloc(sizeof(char *) * (*comps)->count + 1);

	i = 0;
	while (i < (*comps)->count)
	{
		int len = ft_strlen(line->envs[i]) + 1;
		(*comps)->suggestions[i] = malloc(sizeof(char) * len);
		ft_strcpy((*comps)->suggestions[i], line->envs[i]);
		i++;
	}
	return (1);
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
