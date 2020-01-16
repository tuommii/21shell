/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:40:59 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 19:16:17 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_sigcont(void)
{
	config_terminal(0);
	listen_signals();
	ioctl(OUTPUT, TIOCSTI, "");
}

static void	handle_resize(void)
{
	tputs(tgetstr("cl", NULL), 1, print_char);
	ioctl(OUTPUT, TIOCSTI, "");
}

void		signal_handler(int sig)
{
	if (sig == SIGTSTP)
	{
		config_terminal(1);
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

void		watch_kill()
{
	if (g_kill)
	{
		config_terminal(1);
		ft_dprintf(2, "Killed with signal, but memory was free'd!\n");
		exit(1);
	}
}

void		listen_signals(void)
{
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTTIN, signal_handler);
	signal(SIGTTOU, signal_handler);
	signal(SIGWINCH, signal_handler);
}
