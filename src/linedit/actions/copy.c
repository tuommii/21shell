/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:00:45 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/12 09:38:05 by mtuomine         ###   ########.fr       */
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
	execve(COPY_PATH, cmd2, envp);
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
	char *echo[4];
	char *copy[COPY_ARR_SIZE];

	echo[0] = "echo";
	echo[1] = "-n";
	echo[2] = line->input;
	echo[3] = (char *)0;
	copy[0] = COPY_NAME;
	if (COPY_PARAM)
	{
		copy[1] = COPY_PARAM;
		copy[2] = COPY_PARAM2;
		copy[3] = (char *)0;
	}
	else
		copy[1] = COPY_PARAM;
	run_copy(echo, copy, line->envp);
	return (1);
}
