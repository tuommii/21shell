/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:26:50 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/12 09:44:05 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

/*
** Returns last item after '/
*/

char		*deepest_folder(char *path)
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

char		*git_branch(char *cwd)
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
	ft_bzero(line->prompt, INPUT_BUFFER);
	ft_strcpy((char *)line->prompt, ">");
	line->prompt_len = 1;
	ft_putstr(FT_GREEN);
	ft_putstr((const char *)line->prompt);
	ft_putstr(FT_RESET);
	return (1);
}

void		print_prompt(t_line *line, char *cwd, char *branch)
{
	int cwd_len;
	int branch_len;

	if (handle_readmore(line))
		return ;
	line->prompt_len = 2;
	if (cwd[0])
	{
		cwd_len = ft_strlen(cwd);
		ft_putstr(FT_GREEN);
		ft_putstr((const char *)cwd);
		line->prompt_len += cwd_len;
	}
	if (branch[0])
	{
		branch_len = ft_strlen(branch);
		ft_putstr(FT_BLUE);
		ft_putstr(" on ");
		ft_putstr(branch);
		line->prompt_len += branch_len + 4;
	}
	ft_putstr((const char *)line->prompt);
	ft_putstr(FT_RESET);
}

void		set_prompt(t_line *line)
{
	char	cwd[INPUT_BUFFER];
	char	*dir;
	char	*branch;

	getcwd(cwd, INPUT_BUFFER);
	load_paths(line->ac, cwd);
	dir = deepest_folder(cwd);
	branch = git_branch(cwd);
	ft_bzero(line->cwd, INPUT_BUFFER);
	if (dir)
		ft_strcpy(line->cwd, dir);
	ft_bzero(line->branch, INPUT_BUFFER);
	if (branch)
		ft_strcpy(line->branch, branch);
	print_prompt(line, line->cwd, line->branch);
	ft_strdel(&dir);
	ft_strdel(&branch);
}
