/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 20:43:28 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void init()
{
	g_kill = 0;
	check_tty();
	config_terminal(0);
	tputs(tgetstr("cl", NULL), 1, print_char);
	startup_banner();
}

int	main(int argc, char **argv, char **environment)
{
	int code;
	if (!argc || !argv || !environment)
		exit(EXIT_FAILURE);
	init();
	code = 0;
	while (1)
	{
		listen_signals();
		watch_kill();
		code = keyboard();
		if (ft_isprint(code))
			ft_printf("%c", code);
	}

	config_terminal(1);
	exit(EXIT_SUCCESS);
}
