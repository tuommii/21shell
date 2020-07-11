/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:26:50 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/11 20:40:29 by mtuomine         ###   ########.fr       */
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

static int handle_readmore(t_line *line)
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
	if (handle_readmore(line))
		return ;
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

void set_prompt(t_line *line)
{
	char	cwd[INPUT_BUFFER];

	getcwd(cwd, INPUT_BUFFER);
	load_paths(line->ac, cwd);
	line->cwd = deepest_folder(cwd);
	line->branch = git_branch(cwd);
	print_prompt(line, line->cwd, line->branch);
}
