/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:05:47 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 08:12:08 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void get_binaries(char **envs)
{
	char **paths;

	paths = ft_strsplit(ft_getenv("PATH", envs), ':');
	int i = 0;
	while (paths != NULL && paths[i])
	{
		ft_printf("%s\n", paths[i]);
		i++;
	}
	if (paths != NULL)
		ft_free_arr(paths);
}
