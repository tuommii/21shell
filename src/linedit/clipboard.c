/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 10:40:07 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/29 21:00:28 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/wait.h"
#include "linedit.h"

void clipboard_set(t_clipboard *clip)
{
	if (clip)
	{

	}
    pid_t pid;
    int fd[2];
    int ret, i;

    ret = pipe(fd);
    if ( ret == -1 )
	{
        perror("pipe error: ");
        exit(1);
    }

    for ( i=0; i<2; i++ )
	{
        pid = fork();
        if ( pid==0 )
            break;
    }

    if ( 2 == i )
	{
        close(fd[0]);
        close(fd[1]);
        while ( i-- )
		{
            if( wait(NULL) == -1 )
			{
                perror("wait error: ");
                exit(1);
            }
        }
    } else if ( 0 == i )
	{
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("echo", "echo", "KOVA KOODATTU", NULL);
    } else if ( 1 == i)
	{
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("xclip", "xclip", NULL);
    }
}

/* COPY UNTIL FIRST NEWLINE*/
void clipboard_update(t_clipboard *clip)
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
        read(p[0], buf, INPUT_BUFFER);
		int j = 0;
		while (buf[j] && buf[j] != '\n')
		{
			clip->content[j] = buf[j];
			j++;
		}
		clip->content[j] = '\0';
    }
}

void clipboard_draw(t_line *line)
{
	int len;
	int i;

	len = ft_strlen(line->clipboard.content);
	if (!len || line->len + ft_strlen(line->clipboard.content) >= INPUT_BUFFER)
		return ;
	if (line->pos != line->len)
	{
		i = -1;
		while (++i < len)
			ft_insert(line->input, line->pos + i + 1, line->clipboard.content[i]);
	}
	else
		ft_strcpy(line->input + line->len, line->clipboard.content);
	line->len += len;
	line->pos += len;
	// if (line->clipboard.is_cut)
	// {
	// 	ft_bzero(line->clipboard.content, INPUT_BUFFER);
	// 	line->clipboard.is_cut = 0;
	// }
	redraw_input(line);
}