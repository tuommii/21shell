/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:35:03 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 16:09:47 by srouhe           ###   ########.fr       */
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
		tputs(tgetstr("ve", NULL), 1, print_char);
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

void setup(int argc, char **argv, char **environment)
{
	if (!argc || !argv || !environment)
		exit(EXIT_FAILURE);
	g_kill = 0;
	check_tty();
	config_terminal(0);
	tputs(tgetstr("cl", NULL), 1, print_char);
	//ascii_art();
}

char	**init_env(char **env)
{
	int		i;
	int		size;
	char	**r;

	size = 0;
	while (env[size])
		size++;
	i = 0;
	if (!(r = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (env[i])
	{
		if (!(r[i] = ft_strdup(env[i])))
			return (NULL);
		i++;
	}
	r[size] = NULL;
	return (r);
}

void	create_shell(char **environ)
{
	g_sh.env = init_env(environ);
	g_sh.hist = NULL;
	g_sh.i = 0;
	g_sh.hist_i = 0;
	g_sh.len = 0;
	g_sh.key = 0;
	g_sh.hist_count = 0;
	// TODO: If doesn't exist
	g_sh.username = getenv("LOGNAME");
	g_sh.username_len = ft_strlen(g_sh.username);
	g_sh.extra = "$>";
	g_sh.extra_len = ft_strlen(g_sh.extra);
	g_sh.prompt_len = g_sh.username_len + g_sh.extra_len;
	g_sh.x = g_sh.prompt_len;
	ft_bzero(g_sh.input, INPUT_BUFFER);
	get_shell_size();
	// Or ascii art rows + 1
	g_sh.y = 0;
}
