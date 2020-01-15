/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 21:32:14 by mtuomine         ###   ########.fr       */
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
	char input[INPUT_BUFFER + 1];
	int	i = 0;

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

		else if (code == ENTER)
		{
			input[i] = '\0';
			ft_printf("\nSAMI WILL PARSE THIS...\n");
			ft_printf("VALUE WAS: [%s]\n", input);
			ft_bzero(input, 4096);
			// input[0] = '\0';
			i = 0;
		}

		else if (code == CTRL_L)
		{
			tputs(tgetstr("cl", NULL), 1, print_char);
		}

		else if (code == ESC)
		{
			ft_printf("\nSHELL IS TOO AWESOME TO EXIT!\n");
		}

		else if (code == LEFT)
		{
			ft_printf("\nLEFT\n");
			ft_dprintf(0, tgoto(CM, 20, 20));
		}

		else if (ft_isprint(code))
		{
			input[i] = (char)code;
			ft_printf("%c", input[i]);
			i++;
		}
	}
	cleanup();
}
