/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:54:55 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/10 13:02:34 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void load_paths(t_completer *ac, char *cwd)
{
	struct dirent *de;
	DIR *dir;
	char **head;

	ac->paths_count = count_files(cwd);
	dir = opendir(cwd);
	if (dir == NULL)
		return ;
	if (!(ac->paths = malloc(sizeof(char *) * (ac->paths_count + 1))))
		return ;
	head = ac->paths;
	while ((de = readdir(dir)) != NULL)
	{
		if (!(*(ac->paths) = malloc(sizeof(char) * ft_strlen(de->d_name) + 1)))
			return ;
		ft_strcpy(*(ac->paths), de->d_name);
		ac->paths++;
	}
	*(ac->paths) = NULL;
	ac->paths = head;
	closedir(dir);
}
