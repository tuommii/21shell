/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 10:40:07 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/11 22:45:16 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/wait.h"
#include "linedit.h"

/*
** Format buffer and copy (until newline) it to clipboard
*/

static void	format_to_clipboard(char *buf, t_clipboard **clip)
{
	int		j;
	char	*formatted;

	formatted = ft_strreplace(buf, "\t", "  ");
	j = 0;
	while (formatted[j] && formatted[j] != '\n' && j < INPUT_BUFFER)
	{
		(*clip)->content[j] = formatted[j];
		j++;
	}
	ft_strdel(&formatted);
	(*clip)->content[j] = '\0';
}

/*
** Runs OS-specific paste command
*/

static void	exec_paste_cmd(pid_t pid, \
t_clipboard **clip, char *paste_cmd[5], int p[2])
{
	extern char	**environ;
	char		buf[INPUT_BUFFER + 1];

	if (pid == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		execve(PASTE_PATH, paste_cmd, environ);
		return ;
	}
	wait(&pid);
	close(p[1]);
	ft_bzero(buf, INPUT_BUFFER + 1);
	read(p[0], buf, INPUT_BUFFER);
	if (buf[0] == '\0')
		return ;
	format_to_clipboard(buf, clip);
}

void		external_paste(t_clipboard *clip)
{
	char	*paste_cmd[PASTE_ARR_SIZE];
	int		p[2];
	pid_t	pid;

	paste_cmd[0] = PASTE_NAME;
	if (PASTE_PARAM)
	{
		paste_cmd[1] = PASTE_PARAM;
		paste_cmd[2] = PASTE_PARAM2;
		paste_cmd[3] = PASTE_PARAM3;
		paste_cmd[4] = (char *)0;
	}
	else
		paste_cmd[1] = PASTE_PARAM;
	pipe(p);
	pid = fork();
	exec_paste_cmd(pid, &clip, paste_cmd, p);
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
