/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:00:45 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/11 19:58:50 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static void handle_id_zero(int p[2], char *cmd1[], char **envp)
{
	close(1);
	dup(p[1]);
	close(p[0]);
	close(p[1]);
	execve("/bin/echo", cmd1, envp);
}

static void handle_else(int p[2], char *cmd2[], char **envp)
{
	close(0);
	dup(p[0]);
	close(p[0]);
	close(p[1]);
	execve("/usr/bin/xclip", cmd2, envp);
}

static int run_copy(char *cmd1[], char *cmd2[], char **envp)
{
	int p[2];
	int status;
	pid_t id;

	if ((id = fork()) == -1)
		return (-1);
	else if (id == 0)
	{
		;
	}
	else
	{
		wait(&status);
		return (status);
	}
	if (pipe(p) < 0)
		return (-1);
	if ((id = fork()) == -1)
		return (-1);
	else if (id == 0)
		handle_id_zero(p, cmd1, envp);
	else
		handle_else(p, cmd2, envp);
	return (0);
}

int	external_copy(t_line *line)
{
	char *echo[3];
	char *copy[4];

	echo[0] = "echo";
	echo[1] = "-n";
	echo[2] = line->input;
	echo[3] = (char *)0;
	copy[0] = "xclip";
	copy[1] = "-selection";
	copy[2] = "clipboard";
	copy[3] = (char *)0;
	run_copy(echo, copy, line->envp);
	return (1);
}
