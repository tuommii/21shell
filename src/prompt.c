/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:53:12 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 18:40:46 by srouhe           ###   ########.fr       */
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

void	print_prompt(void)
{
	// char	host[INPUT_BUFFER + 1];
	//char	cwd[INPUT_BUFFER + 1];
	char *logname = getenv("LOGNAME");
	ft_printf(tgoto(tgetstr("cm", NULL), 0, g_sh.y));
	// gethostname(host, INPUT_BUFFER);
	//getcwd(cwd, INPUT_BUFFER);
	// ft_printf("\033[%d;%df\033", g_sh.y+1, 0);
	ft_printf(GREEN);
	ft_printf("%s", logname);
	// ft_printf("@");
	// ft_printf(FT_BOLD_BLUE);
	// ft_printf("%s: ", host);
	ft_printf(NORMAL);
	ft_printf("%s", g_sh.extra);
}

void	print_input(void)
{
	// ft_printf("%-s", g_sh.input);

	// if (g_sh.len + g_sh.prompt_len > 20)
	// {
	// 	ft_printf(tgoto(tgetstr("cm", NULL), g_sh.prompt_len + 1, g_sh.y));
	// }
	// int cols = g_sh.cols;
	// static int len = g_sh.len
	ft_printf("\033[s");
	ft_printf(tgoto(tgetstr("cm", NULL), g_sh.prompt_len, g_sh.y));
	// Wthout len backspaace deleteing char dooesnt print?
	ft_printf("%-*s", g_sh.len, g_sh.input);
	ft_printf("\033[u");
	// ft_printf("\033[%d;%df%-*s\033[u", g_sh.y, g_sh.prompt_len + 1, g_sh.len, g_sh.input);
	//ft_printf("\033[u");
}

void	get_shell_size(void)
{
	struct winsize w;

	ioctl(OUTPUT, TIOCGSIZE, &w);
	g_sh.rows = w.ws_row;
	g_sh.cols = w.ws_col;
}
