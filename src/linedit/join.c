/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:00:45 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/11 17:27:11 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static void handle_id_zero(int p[2], char *com1[], char **envp)
{
	close(1);
	dup(p[1]);
	close(p[0]);
	close(p[1]);
	execve("/bin/echo", com1, envp);
}

static void handle_else(int p[2], char *com2[], char **envp)
{
	close(0);
	dup(p[0]);
	close(p[0]);
	close(p[1]);
	execve("/usr/bin/xclip", com2, envp);
}

int join(char *com1[], char *com2[], char **envp)
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
		handle_id_zero(p, com1, envp);
	else
		handle_else(p, com2, envp);
	return (0);
}
