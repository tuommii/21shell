/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:53:12 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/05 12:02:24 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ascii_art(void)
{
	int		fd;
	char	*line;

	if ((fd = open(".boot", O_RDWR)) < 0)
		return ;
	while (get_next_line(fd, &line))
	{
		ft_putendl_fd(line, OUTPUT);
		ft_strdel(&line);
	}
	close(fd);
}

void	print_prompt(t_shell *sh)
{
	// char	host[INPUT_BUFFER + 1];
	//char	cwd[INPUT_BUFFER + 1];
	char *logname = getenv("LOGNAME");
	// gethostname(host, INPUT_BUFFER);
	//getcwd(cwd, INPUT_BUFFER);
	// ft_printf("\033[%d;%df\033", sh->y+1, 0);
	ft_printf(FT_GREEN);
	ft_printf("%s", logname);
	// ft_printf("@");
	// ft_printf(FT_BOLD_BLUE);
	// ft_printf("%s: ", host);
	ft_printf(FT_RESET);
	ft_printf("%s", sh->extra);
}

void	print_debug(t_shell *sh)
{
	// ft_printf("\033[s");
	// ft_printf("\033[1;1f %10s: [%3d, %3d]\033[u", "CURSOR X", sh->x, sh->y);
	// ft_printf("\033[2;1f %10s: [%3d]\033[u", "INDEX", sh->i);
	// ft_printf("\033[3;1f %10s: [%3d]\033[u", "KEY", sh->key);
	// ft_printf("\033[4;1f %10s: [%3d]\033[u", "LEN", sh->len);
	// ft_printf("\033[5;1f %10s: [%-70s]\033[u", "INPUT", sh->input);
	// ft_printf("\033[6;1f %10s: [%3d, %3d]\033[u", "HIST", sh->hist_i, sh->hist_count);
	// ft_printf("\033[u");
}

void	print_input(t_shell *sh)
{
	ft_printf("\033[s");
	ft_printf(tgoto(tgetstr("cm", NULL), sh->prompt_len, sh->y));
	ft_printf("%-*s", sh->len, sh->input);
	ft_printf("\033[u");
}

void	get_shell_size(t_shell *sh)
{
	struct winsize w;

	ioctl(OUTPUT, TIOCGSIZE, &w);
	sh->rows = w.ws_row;
	sh->cols = w.ws_col;
}
