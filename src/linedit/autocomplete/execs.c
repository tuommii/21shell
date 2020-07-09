/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:05:47 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/09 22:32:07 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// TODO: check is file and is executable
void files_from_dir(t_completer *ac, char *path, int *i)
{
	struct dirent *de;
	DIR *dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		ft_printf("\nOPEN DIR 1 count ERROR!\n");
	}

	while ((de = readdir(dir)) != NULL)
	{
		ac->execs[*i] = malloc(sizeof(char) * ft_strlen(de->d_name) + 1);
		ft_strcpy(ac->execs[*i], de->d_name);
		*i += 1;
	}

	if ((closedir(dir)) == -1)
	{
		ft_printf("\nOPEN DIR 1 count ERROR!\n");
	}
}

int count_files(char *path)
{
	DIR *dir;

	if (!path)
		return (0);

	dir = opendir(path);
	if (dir == NULL)
	{
		ft_printf("\nOPEN DIR 1 count ERROR!\n");
		return (0);
	}

	// get count
	int i = 0;
	while (readdir(dir) != NULL)
		i++;
	if ((closedir(dir)) == -1)
	{
		ft_printf("\nOPEN DIR 1 count ERROR!\n");
		return (0);
	}
	return (i);
}

// opendir is allowed
void load_execs(t_completer *ac, char **envs)
{
	char **paths;

	paths = NULL;
	if (!(paths = ft_strsplit(ft_getenv("PATH", envs), ':')))
		return ;

	char **h = paths;
	while (*paths != NULL)
	{
		ac->execs_count += count_files(*paths);
		paths++;
	}


	paths = h;


	if (!(ac->execs = malloc(sizeof(char *) * (ac->execs_count + 1))))
	{
		ft_freestrarr(paths);
		return ;
	}

	// char **head;
	// head = NULL;
	// head = ac->execs;

	// int j = 0;
	int i = 0;
	while (*paths != NULL)
	{
		files_from_dir(ac, *paths, &i);
		paths++;
		// j++;
	}
	ft_freestrarr(h);

	// ac->execs = head;

	// if (!(files = files_from_dir("/bin/")))
	// 	return (NULL);
	// if (paths != NULL)
	// 	ft_free_arr(paths);
}
