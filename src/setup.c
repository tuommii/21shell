/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:35:03 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/17 12:42:20 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_char(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

void	config_terminal(int reset)
{
	static struct termios backup;
	static struct termios new_config;

	if (reset)
	{
		tputs(tgetstr("te", NULL), 1, print_char);
		tputs(tgetstr("vs", NULL), 1, print_char);
		tcsetattr(OUTPUT, TCSANOW, &backup);
	}
	else
	{
		tcgetattr(OUTPUT, &backup);
		new_config = backup;
		new_config.c_lflag &= ~(ECHO | ICANON);
		new_config.c_cc[VMIN] = 1;
		new_config.c_cc[VTIME] = 0;
		tcsetattr(OUTPUT, TCSANOW, &new_config);
		tputs(tgetstr("ti", NULL), 1, print_char);
		tputs(tgetstr("vs", NULL), 1, print_char);
	}
}

void	check_tty(void)
{
	char buffer[2048];
	char *name;

	if (!(name = getenv("TERM")))
	{
		ft_dprintf(OUTPUT, "No terminal name");
		exit(1);
	}
	if (!isatty(OUTPUT))
	{
		ft_dprintf(OUTPUT, "No terminal detected!\n");
		exit(1);
	}
	if (tgetent(buffer, name) != 1)
	{
		ft_dprintf(OUTPUT, "No database or No entry found\n");
		exit(1);
	}
}

void init_shell(int argc, char **argv, char **environment)
{
	if (!argc || !argv || !environment)
		exit(EXIT_FAILURE);
	g_kill = 0;
	check_tty();
	config_terminal(0);
	tputs(tgetstr("cl", NULL), 1, print_char);
	ascii_art();
}

t_shell *create_shell(void)
{
	t_shell *sh;

	sh = (t_shell *)ft_memalloc(sizeof(t_shell));
	sh->i = 0;
	sh->y = 0;
	sh->len = 0;
	sh->key = 0;
	// TODO: If doesn't exist
	sh->username = getenv("LOGNAME");
	sh->username_len = ft_strlen(sh->username);
	sh->extra = "$>";
	sh->extra_len = ft_strlen(sh->extra);
	sh->prompt_len = sh->username_len + sh->extra_len;
	sh->x = sh->prompt_len;
	ft_bzero(sh->input, INPUT_BUFFER);
	get_shell_size(sh);
	return (sh);
}
