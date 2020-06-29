/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:43:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/06/29 13:40:42 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_sigcont(void)
{
	g_cont = 1;
	linedit_config(0);
	listen_signals();
	ioctl(OUTPUT, TIOCSTI, "");
}

static void	handle_resize(void)
{
	ioctl(OUTPUT, TIOCSTI, "");
}

/*
** TODO: Is g_kill neccessary?
*/

void		signal_handler(int sig)
{
	if (sig == SIGTSTP)
	{
		linedit_config(1);
		signal(SIGTSTP, SIG_DFL);
		ioctl(OUTPUT, TIOCSTI, "\x1A");
	}
	else if (sig == SIGCONT)
		handle_sigcont();
	else if (sig == SIGWINCH)
		handle_resize();
	else
	{
		g_kill = 1;
		ioctl(OUTPUT, TIOCSTI, "");
	}
}

void		watch_kill(t_line *line)
{
	if (g_cont)
	{
		redraw_input(line);
	}
	else if (g_kill)
	{
		erase_input(line);
		ioctl(OUTPUT, TIOCSTI, "\n");
		g_kill = 0;
		// linedit_exit(line);
	}
}

void		listen_signals(void)
{
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTTIN, signal_handler);
	signal(SIGTTOU, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGINT, signal_handler);
}
