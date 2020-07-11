/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:26:50 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/11 13:05:39 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

/*
** Returns last item after '/
*/

char	*deepest_folder(char *path)
{
	int delta;
	int i;
	int len;

	i = 0;
	while (path[i])
		i++;
	len = i;
	delta = 0;
	while (i > 0 && path[i] != '/')
	{
		delta++;
		i--;
	}
	if (i == 0 && path[0] != '/')
		return (NULL);
	if (path[0] && path[1])
		delta--;
	return (ft_strdup(path + (len - delta)));
}

char	*git_branch(char *cwd)
{
	char	*line;
	char	*path;
	char	*branch;
	int		fd;

	path = ft_pathjoin(cwd, ".git/HEAD");
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (NULL);
	get_next_line(fd, &line);
	branch = deepest_folder(line);
	free(line);
	return (branch);
}

static int	handle_readmore(t_line *line)
{
	if (!line->readmore)
		return (0);
	ft_strcpy((char *)line->prompt, ">");
	line->prompt_len = 1;
	ft_putstr(FT_GREEN);
	ft_putstr((char *)line->prompt);
	ft_putstr(FT_RESET);
	return (1);
}

void		print_prompt(t_line *line, char *cwd, char *branch)
{
	if (line->readmore)
	{
		ft_bzero(line->prompt, INPUT_BUFFER);
		ft_strcpy((char *)line->prompt, ">");
		line->prompt_len = 1;
		ft_putstr(FT_GREEN);
		ft_putstr((const char *)line->prompt);
		ft_putstr(FT_RESET);
		return ;
	}
	line->prompt_len = 2;
	if (cwd)
	{
		int cwd_len = ft_strlen(cwd);
		ft_putstr(FT_GREEN);
		ft_putstr((const char *)cwd);
		line->prompt_len += cwd_len;
	}
	if (branch)
	{
		int branch_len = ft_strlen(branch);
		ft_putstr(FT_BLUE);
		ft_putstr(" on ");
		ft_putstr(branch);
		line->prompt_len += branch_len + 4;
	}
	ft_putstr((const char *)line->prompt);
	ft_putstr(FT_RESET);
}

// void branch(pid_t pid, char *git_cmd[5], int p[2], t_line *line)
// {
// 	char		buf[INPUT_BUFFER + 1];
// 	int			j;
// 	char		*formatted;

// 	line->branch = NULL;
// 	if (pid == 0)
// 	{
// 		dup2(p[1], STDOUT_FILENO);
// 		close(p[0]);
// 		if (execve("/usr/bin/git", git_cmd, line->envp) == -1)
// 		{
// 			line->branch = NULL;
// 			return ;
// 		}
// 		return (NULL);
// 	}
// 	wait(&pid);
// 	int status;
// 	if (status = WEXITSTATUS(pid) != -2)
// 	{
// 		ft_printf("\nstatus: %d\n", status);
// 		line->branch = NULL;
// 		return ;
// 	}
// 	close(p[1]);
// 	ft_bzero(buf, INPUT_BUFFER);
// 	read(p[0], buf, INPUT_BUFFER);
// 	ft_printf("\n%s\n", buf);
// 	int len = ft_strlen(buf);
// 	if (!len);
// 	{
// 		line->branch = NULL;
// 		return ;
// 	}
// 	line->branch = malloc(sizeof(char) * (len));
// 	ft_memcpy(line->branch, buf, len-1);
// 	line->branch[len-1] = '\0';
// 	return ;
// }

// void get_branch(t_line *line)
// {
// 	char	*git_cmd[5];
// 	int		p[2];
// 	pid_t	pid;

// 	git_cmd[0] = "git";
// 	git_cmd[1] = "symbolic-ref";
// 	git_cmd[2] = "--short";
// 	git_cmd[3] = "HEAD";
// 	git_cmd[4] = (char *)0;
// 	pipe(p);
// 	pid = fork();
// 	branch(pid, git_cmd, p, line);
// }





/*
** void		print_prompt(t_line *line)
** {
** 	// char	host[INPUT_BUFFER + 1];
** 	// gethostname(host, INPUT_BUFFER);
** 	char *prompt;
** 	char *branch;
** 	char *temp;
** 	char *temp2;
** 	char	cwd[INPUT_BUFFER + 1];
** 	ft_bzero(line->prompt, INPUT_BUFFER);
** 	if (handle_readmore(line))
** 		return ;
** 	getcwd(cwd, INPUT_BUFFER);
** 	// ft_printf("\n%s\n", line->ac->paths[0]);
** 	// ft_printf("\n%s\n", line->ac->paths[1]);
** 	// ft_printf("\n%s\n", line->ac->paths[2]);
** 	char *dir = deepest_folder(cwd);
** 	if (!(branch = git_branch(cwd)))
** 	{
** 		prompt = ft_strjoin(dir, "$>");
** 	}
** 	else
** 	{
** 		temp = ft_strjoin(dir, " on git:");
** 		temp2 = ft_strjoin(temp, branch);
** 		prompt = ft_strjoin(temp2, "$>");
** 		free(temp);
** 		free(temp2);
** 		free(branch);
** 	}
** 	free(dir);
** 	ft_strcpy(line->prompt, prompt);
** 	free(prompt);
** 	line->prompt_len = ft_strlen(line->prompt);
** 	ft_putstr(FT_GREEN);
** 	if (!line->was_copy)
** 		ft_putstr(line->prompt);
** 	ft_putstr(FT_RESET);
** 	line->was_copy = 0;
** }
*/
