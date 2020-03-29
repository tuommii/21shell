/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 10:40:07 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/29 10:59:18 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/wait.h"
#include "linedit.h"

void new_paste(t_line *line)
{
    char *ls[] = {"xclip", "-o", NULL};
    char buf[INPUT_BUFFER + 1];
    int p[2];
    pid_t pid;
    extern char **environ;

    pipe(p);
    pid = fork();
    if (pid == 0)
    {
        dup2(p[1], STDOUT_FILENO);
        close(p[0]);
        execve("/usr/bin/xclip", ls, environ);
    }
    else {
        wait(&pid);
        close(p[1]);
        read(p[0], buf, INPUT_BUFFER); //mikä buffsize
		ft_strcpy(line->input, buf);
		line->len = ft_strlen(buf);
		redraw_input(line);
        // printf("Miikka: %s", buf);
    }
	// Testi copy
}
