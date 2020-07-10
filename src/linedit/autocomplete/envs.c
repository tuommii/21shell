/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:03:03 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/10 13:48:36 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static int	get_envname_last_index(char *str)
{
	char	*cpy;
	int		i;

	cpy = str;
	i = 0;
	while (cpy[i] && cpy[i] != '=')
		i++;
	return (i);
}

static int	count_envs(char **envs)
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

static int	ft_env_exists(char *name, char *given, int len_given)
{
	if (ft_strncmp(name, given, len_given) == 0 \
	&& name[len_given] && name[len_given] == '=')
		return (1);
	return (0);
}

void		load_envs(t_completer *ac, char **envs)
{
	char	**cpy;
	char	**head;
	int		i;
	int		last;

	ac->envs_count = count_envs(envs);
	if (!(ac->envs = malloc(sizeof(char *) * (ac->envs_count + 1))))
		return ;
	head = ac->envs;
	i = 0;
	while (i < ac->envs_count)
	{
		last = get_envname_last_index(envs[i]);
		ac->envs[i] = malloc(sizeof(char) * last + 1);
		ft_strncpy(ac->envs[i], envs[i], last);
		ac->envs[i][last] = '\0';
		i++;
	}
	ac->envs[i] = NULL;
	ac->envs = head;
}

char		*ft_getenv(char *name, char **envs)
{
	int i;
	int len;

	len = ft_strlen(name);
	if (!name || ft_strequ(name, "$"))
		return (NULL);
	i = 0;
	while (envs[i])
	{
		if (ft_env_exists(envs[i], name, len))
			return (&envs[i][len + 1]);
		i++;
	}
	return (NULL);
}
