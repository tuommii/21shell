/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:05:47 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 15:21:14 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// TODO: check is file and is executable
static char **files_from_dir(char *path)
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

	// get count
	int i = 0;
	while (readdir(dir) != NULL)
		i++;
	closedir(dir);

	ft_printf("\nCOUNT: %d\n", i);

	if (!(execs = malloc(sizeof(char *) * i)))
	{
		ft_printf("\nMALLOC ERR: %d\n", i);
		return (NULL);
	}

	dir = opendir(path);
	if (dir == NULL)
	{
		ft_printf("\nOPEN DIR 2 ERROR!\n");
		return (NULL);
	}

	i = 0;
	while ((de = readdir(dir)) != NULL)
	{
		execs[i] = malloc(sizeof(char) * ft_strlen(de->d_name) + 1);
		ft_strcpy(execs[i], de->d_name);
		i++;
	}
	execs[i] = NULL;
	closedir(dir);
	return (execs);
}

// opendir is allowed
char **get_execs(char **envs)
{
	char **paths;
	char **files;

	paths = ft_strsplit(ft_getenv("PATH", envs), ':');
	int i = 0;
	// while (paths != NULL && paths[i])
	// {
		//ft_printf("%s\n", paths[i]);
		// i++;
	// }
	files = files_from_dir("/bin/");
	if (*files == NULL)
		ft_printf("\nvittu..\n");
	if (paths != NULL)
		ft_free_arr(paths);
	return (files);
}
