/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:53:12 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 20:51:10 by srouhe           ###   ########.fr       */
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

static char		*prompt_prefix(void)
{
	char	*user;
	char	*tmp;
	char	*r;

	user = getenv("USER") ? getenv("USER") : getenv("LOGNAME");
	if (user)
	{
		tmp = ft_strjoin(user, "@");
		r = ft_strjoin(tmp, "21sh");
		free(tmp);
		return (r);
	}
	return (NULL);
}

char			*parse_path(char *cwd)
{
	char	*home;

	if (!cwd)
		return (NULL);
	home = getenv("HOME");
	if (!home)
		return (ft_strdup(cwd));
	else if (!ft_strstr(cwd, home))
		return (ft_strdup(cwd));
	else if (ft_strequ(cwd, home))
		return (ft_strdup("~"));
	else
		return (ft_pathjoin("~", cwd + ft_strlen(home)));
}

/*
**		Display prompt message.
**		Format: user@hostname:pwd>
*/

void			print_prompt(void)
{
	char	*prefix;
	char	*prompt;
	char	buffer[BUF_SIZE + 1];

	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, g_sh.y), OUTPUT);
	getcwd(buffer, BUF_SIZE);
	prefix = prompt_prefix();
	prompt = parse_path(buffer);
	if (prefix)
		ft_printf("%s%s%s:", GREEN, prefix, NORMAL);
	ft_printf("%s%s%s: ", BLUE, prompt, NORMAL);
	g_sh.prompt_len = ft_strlen(prefix) + ft_strlen(prompt) + 3;
	g_sh.x = g_sh.prompt_len;
	ft_strdel(&prefix);
	ft_strdel(&prompt);
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
