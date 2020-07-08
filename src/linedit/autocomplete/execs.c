/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:05:47 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/08 09:03:44 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"


t_completer *create_completer(void)
{
	t_completer *ac;

	ac = NULL;
	if (!(ac = malloc(sizeof(t_completer))))
		return (NULL);

	int i = 0;
	while (i < MAX_MATCHES)
	{
		ac->matches[i] = NULL;
		i++;
	}

	ac->len = 0;
	ac->word = NULL;
	ac->matches_count = 0;
	ac->ctx = NULL;
	ac->suggestions = NULL;
	ac->count = 0;
	return (ac);
}

// TODO: check is file and is executable
char **files_from_dir(t_completer **ac, char *path, int *i)
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

	ft_printf("STARTING WHILE WITH I: %d\n", *i);
	while ((de = readdir(dir)) != NULL)
	{
		(*ac)->execs[*i] = malloc(sizeof(char) * ft_strlen(de->d_name) + 1);
		ft_strcpy((*ac)->execs[*i], de->d_name);
		ft_printf("\n%d: %s\n", *i, (*ac)->execs[*i]);
		*i += 1;
	}

	closedir(dir);
	return (execs);
}

static int count_files(char *path)
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
char **get_execs(t_completer *ac, char **envs)
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
	ft_printf("\nCOUNTED: %d\n", ac->execs_count);

	if (!(ac->execs = malloc(sizeof(char *) * ac->execs_count + 1)))
	{
		ft_printf("\nMALLOC ERR: %d\n", i);
		return (NULL);
	}

	int j = 0;
	int k = 0;
	while (paths != NULL && paths[j])
	{
		ft_printf("Looking: %s\n", paths[j]);
		files_from_dir(&ac, paths[j], &k);
		j++;
	}


	// if (!(files = files_from_dir("/bin/")))
	// 	return (NULL);
	// if (paths != NULL)
	// 	ft_free_arr(paths);
	return (files);
}
