/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:26:50 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/10 15:37:00 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

/*
** Returns last item after '/
*/

static char	*deepest_folder(char *path)
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

static char	*git_branch(char *cwd)
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
	if (!line->was_copy)
		ft_putstr((char *)line->prompt);
	ft_putstr(FT_RESET);
	line->was_copy = 0;
	return (1);
}

void		print_prompt(t_line *line)
{
	if (line->readmore)
	{
		ft_bzero(line->prompt, INPUT_BUFFER);
		ft_strcpy((char *)line->prompt, ">");
		line->prompt_len = 1;
		ft_putstr(FT_GREEN);
		if (!line->was_copy)
			ft_putstr((const char *)line->prompt);
		ft_putstr(FT_RESET);
		line->was_copy = 0;
		return ;
	}
	ft_putstr(FT_GREEN);
	if (!line->was_copy)
		ft_putstr((const char *)line->prompt);
	line->was_copy = 0;
	ft_putstr(FT_RESET);
}

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
