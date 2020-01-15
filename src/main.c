/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 20:59:02 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void init(int argc, char **argv, char **environment)
{
	if (!argc || !argv || !environment)
		exit(EXIT_FAILURE);
	g_kill = 0;
	check_tty();
	config_terminal(0);
	tputs(tgetstr("cl", NULL), 1, print_char);
	startup_banner();
}

static void cleanup()
{
	config_terminal(1);
	return exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **environment)
{
	int code;

	init(argc, argv, environment);
	code = 0;
	while (1)
	{
		listen_signals();
		watch_kill();
		code = keypress();

		if (code == TAB)
		{
			ft_printf("AUTOCOMPLETE COMING...\n");
		}

		if (code == ENTER)
		{
			ft_printf("\nSAMI WILL PARSE THIS...\n");
		}

		if (code == CTRL_L)
		{
			tputs(tgetstr("cl", NULL), 1, print_char);
		}

		if (code == ESC)
		{
			ft_printf("\nSHELL IS TOO GOOD TO EXIT!\n");
		}

		if (ft_isprint(code))
			ft_printf("%c", code);
	}
	cleanup();
}
