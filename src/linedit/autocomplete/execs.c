/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:05:47 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/09 17:11:51 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// TODO: check is file and is executable
char **files_from_dir(t_completer *ac, char *path, int *i)
{
	struct dirent *de;
	DIR *dir;
	char **execs;

	dir = opendir(path);
	if (dir == NULL)
	{
		ft_printf("\nOPEN DIR 1 count ERROR!\n");
		return (NULL);
	}

	while ((de = readdir(dir)) != NULL)
	{
		ac->execs[*i] = malloc(sizeof(char) * ft_strlen(de->d_name) + 1);
		ft_strcpy(ac->execs[*i], de->d_name);
		*i += 1;
	}

	closedir(dir);
	return (execs);
}

int count_files(char *path)
{
	DIR *dir;

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
	closedir(dir);
	return (i);
}

// opendir is allowed
char **load_execs(t_completer *ac, char **envs)
{
	char **paths;
	char **files;

	files = NULL;
	paths = ft_strsplit(ft_getenv("PATH", envs), ':');

	int i = 0;
	ac->execs_count = 0;

	while (paths != NULL && paths[i])
	{
		ac->execs_count += count_files(paths[i]);
		i++;
	}

	if (!(ac->execs = malloc(sizeof(char *) * ac->execs_count + 1)))
	{
		ft_printf("\nMALLOC ERR: %d\n", i);
		ft_freestrarr(paths);
		return (NULL);
	}

	char **head = ac->execs;

	int j = 0;
	int k = 0;
	while (paths != NULL && paths[j])
	{
		files_from_dir(ac, paths[j], &k);
		j++;
	}
	ft_freestrarr(paths);


	// if (!(files = files_from_dir("/bin/")))
	// 	return (NULL);
	// if (paths != NULL)
	// 	ft_free_arr(paths);
	return (head);
}
