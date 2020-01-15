/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 20:21:56 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void init()
{
	g_kill = 0;
	check_tty();
	config_terminal(0);
	tputs(tgetstr("cl", NULL), 1, print_char);
}

int	main(int argc, char **argv, char **environment)
{
	if (!argc || !argv || !environment)
		exit(EXIT_FAILURE);

	init();

	while (1)
	{
		listen_signals();
		watch_kill();

	}

	config_terminal(1);
	exit(EXIT_SUCCESS);
}
