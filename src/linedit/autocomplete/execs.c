/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:05:47 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/12 18:13:06 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void	files_from_dir(t_completer *ac, char *path, int *i)
{
	struct dirent	*de;
	DIR				*dir;

	dir = opendir(path);
	if (dir == NULL)
		return ;
	while ((de = readdir(dir)) != NULL)
	{
		ac->execs[*i] = malloc(sizeof(char) * ft_strlen(de->d_name) + 1);
		ft_strcpy(ac->execs[*i], de->d_name);
		*i += 1;
	}
	if ((closedir(dir)) == -1)
	{
		ft_putstr("Error while closing dir\n");
		return ;
	}
}

int		count_files(char *path)
{
	DIR *dir;
	int i;

	if (!path)
		return (0);
	dir = opendir(path);
	if (dir == NULL)
	{
		ft_putstr("Error while opening dir\n");
		return (0);
	}
	i = 0;
	while (readdir(dir) != NULL)
		i++;
	if ((closedir(dir)) == -1)
	{
		ft_putstr("Error while closing dir\n");
		return (0);
	}
	return (i);
}

void	load_execs(t_completer *ac, char **envs)
{
	char	**paths;
	char	**head;
	int		i;

	if (!(paths = ft_strsplit(ft_getenv("PATH", envs), ':')))
		return ;
	head = paths;
	while (*head != NULL)
	{
		ac->execs_count += count_files(*head);
		head++;
	}
	head = paths;
	if (!(ac->execs = ft_memalloc(sizeof(char *) * (ac->execs_count + 1))))
	{
		ft_freestrarr(paths);
		return ;
	}
	i = 0;
	while (*head != NULL)
	{
		files_from_dir(ac, *head, &i);
		head++;
	}
	ft_freestrarr(paths);
}
