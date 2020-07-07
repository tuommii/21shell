/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:03:03 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 08:55:07 by mtuomine         ###   ########.fr       */
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

int suggestions_env(t_line *line, t_completer **ac)
{
	char **cpy;
	int i;

	if (ft_strcmp((*ac)->ctx, CTX_ENV) != 0)
		return (0);

	(*ac)->count = count_envs(line->envs);
	(*ac)->suggestions = malloc(sizeof(char *) * (*ac)->count + 1);

	i = 0;
	while (i < (*ac)->count)
	{
		int len = ft_strlen(line->envs[i]) + 1;
		(*ac)->suggestions[i] = malloc(sizeof(char) * len);
		ft_strcpy((*ac)->suggestions[i], line->envs[i]);
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
