/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:54:55 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/08 15:09:20 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void load_paths(t_completer *ac, char *cwd)
{
	struct dirent *de;
	DIR *dir;

	ac->paths_count = count_files(cwd);

	dir = opendir(cwd);
	if (dir == NULL)
	{
		ft_printf("\nOPEN DIR 1 count ERROR!\n");
		return ;
	}


	ac->paths = malloc(sizeof(char *) * ac->paths_count);

	int i = 0;
	while ((de = readdir(dir)) != NULL)
	{
		// TODO: Checl all mallocs
		ac->paths[i] = malloc(sizeof(char) * ft_strlen(de->d_name) + 1);
		ft_strcpy(ac->paths[i], de->d_name);
		i++;
	}

	ac->paths[i] = NULL;

	closedir(dir);
}
