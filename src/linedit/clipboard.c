/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 10:40:07 by mtuomine          #+#    #+#             */
/*   Updated: 2020/06/22 10:45:59 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/wait.h"
#include "linedit.h"

static void	check_pid(pid_t pid, t_clipboard **clip, char *cpycmd[3], int p[2])
{
	extern char	**environ;
	char		buf[INPUT_BUFFER + 1];
	int			j;

	if (pid == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		execve(COPY_PATH, cpycmd, environ);
	}
	else
	{
		wait(&pid);
		close(p[1]);
		ft_bzero(buf, INPUT_BUFFER + 1);
		read(p[0], buf, INPUT_BUFFER);
		j = 0;
		while (buf[j] && buf[j] != '\n')
		{
			(*clip)->content[j] = buf[j];
			j++;
		}
		(*clip)->content[j] = '\0';
	}
}

/*
** Copy until first newline
*/

void		clipboard_update(t_clipboard *clip)
{
	char	*copy_cmd[3];
	int		p[2];
	pid_t	pid;

	copy_cmd[0] = COPY_CMD;
	copy_cmd[1] = COPY_PARAM;
	copy_cmd[2] = NULL;
	pipe(p);
	pid = fork();
	check_pid(pid, &clip, copy_cmd, p);
}

void		clipboard_draw(t_line *line)
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
			ft_insert(line->input, line->pos + i + 1, \
			line->clipboard.content[i]);
	}
	else
		ft_strcpy(line->input + line->len, line->clipboard.content);
	line->len += len;
	line->pos += len;
	redraw_input(line);
}
