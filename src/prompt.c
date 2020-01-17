/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:53:12 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/17 11:39:37 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ascii_art(void)
{
	int		fd;
	char	*line;

	if ((fd = open(".boot", O_RDWR)) < 0)
		return ;
	while (get_next_line(fd, &line))
		ft_putendl_fd(line, OUTPUT);
	close(fd);
}

void	print_prompt(t_shell *sh)
{
	// char	host[INPUT_BUFFER + 1];
	//char	cwd[INPUT_BUFFER + 1];
	char *logname = getenv("LOGNAME");
	// gethostname(host, INPUT_BUFFER);
	//getcwd(cwd, INPUT_BUFFER);
	ft_printf(FT_GREEN);
	ft_printf("%s", logname);
	// ft_printf("@");
	// ft_printf(FT_BOLD_BLUE);
	// ft_printf("%s: ", host);
	ft_printf(FT_RESET);
	ft_printf("%s", sh->extra);
}

void print_debug(t_shell *sh)
{
	ft_printf("\033[s");
	ft_printf("\033[1;1f CURSOR: [x:%d, y:%d]\033[u", sh->x, sh->y);
	ft_printf("\033[2;1f INDEX: [%d]\033[u", sh->i);
	ft_printf("\033[3;1f INPUT: [%-70s]\033[u", sh->input);
	ft_printf("\033[4;1f KEY: [%d]\033[u", sh->key);
	ft_printf("\033[u");
}

void print_input(t_shell *sh)
{
	ft_printf("\033[s");
	ft_printf("\033[24;11f%-*s\033[u", sh->len, sh->input);
	ft_printf("\033[u");
}
