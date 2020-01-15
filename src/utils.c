/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:11:39 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/15 22:12:56 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		startup_banner(void)
{
	int		fd;
	char	*line;

	if ((fd = open(".boot", O_RDWR)) < 0)
		return ;
	while (get_next_line(fd, &line))
		ft_putendl_fd(line, OUTPUT);
	close(fd);
}
