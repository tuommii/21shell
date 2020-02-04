/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:53:12 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/04 20:08:12 by srouhe           ###   ########.fr       */
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
	ft_printf(GREEN);
	ft_printf("%s", logname);
	// ft_printf("@");
	// ft_printf(FT_BOLD_BLUE);
	// ft_printf("%s: ", host);
	ft_printf(NORMAL);
	ft_printf("%s", sh->extra);
}

void	print_input(t_shell *sh)
{
	// ft_printf("%-s", sh->input);

	// if (sh->len + sh->prompt_len > 20)
	// {
	// 	ft_printf(tgoto(tgetstr("cm", NULL), sh->prompt_len + 1, sh->y));
	// }
	// int cols = sh->cols;
	// static int len = sh->len
	ft_printf("\033[s");
	ft_printf(tgoto(tgetstr("cm", NULL), sh->prompt_len, sh->y));
	// Wthout len backspaace deleteing char dooesnt print?
	ft_printf("%-*s", sh->len, sh->input);
	ft_printf("\033[u");
	// ft_printf("\033[%d;%df%-*s\033[u", sh->y, sh->prompt_len + 1, sh->len, sh->input);
	//ft_printf("\033[u");
}

void	get_shell_size(t_shell *sh)
{
	struct winsize w;

	ioctl(OUTPUT, TIOCGSIZE, &w);
	sh->rows = w.ws_row;
	sh->cols = w.ws_col;
}
