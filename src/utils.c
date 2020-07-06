/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 12:24:19 by srouhe            #+#    #+#             */
/*   Updated: 2020/07/06 11:07:44 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Initialize environment variable array
*/

// I might need this also
char	**init_env(char **env)
{
	int		i;
	int		size;
	char	**r;

	size = 0;
	while (env[size])
		size++;
	i = 0;
	if (!(r = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (env[i])
	{
		if (!(r[i] = ft_strdup(env[i])))
			return (NULL);
		i++;
	}
	r[size] = NULL;
	return (r);
}

void		create_shell(char **environ, t_line *line)
{
	g_sh.env = init_env(environ);
	g_sh.line = line;
}

/*
** Cleanup on exit
*/

void		cleanup(t_line *line)
{
	toggle_raw(1, 0);
	erase_input(line);
	free_history(&line->hist);
	free(line);
	ft_freestrarr(g_sh.env);
	exit(EXIT_SUCCESS);
}

/*
** Fatal errors
*/

void		exit_error(int err, char *msg)
{
	err == MALLOC_ERROR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == FORK_ERR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == EXECVE_ERROR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == DUP_ERR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == REDIR_ERR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	exit(err);
}

/*
** Print non fatal errors
*/

void		print_error(int err, char *msg)
{
	if (err == SYNTAX_ERR)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", STR_SYNTAX_ERR, msg);
	else if (err == PERMISSION_ERR)
		ft_dprintf(STDERR_FILENO, "%s %s\n", STR_PERMISSION_ERR, msg);
	else if (err == ENOENT)
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", msg, STR_NOT_FOUND_ERR);
	else if (err == ENOTDIR)
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", msg, STR_NOT_DIR_ERR);
	else if (err == EISDIR)
		ft_dprintf(STDERR_FILENO, "%s %s\n", STR_IS_DIR, msg);
	else if (err == AMB_REDIR_ERR)
		ft_dprintf(STDERR_FILENO, "%s %s\n", STR_AMB_REDIR_ERR, msg);
	else if (err == PIPE_ERR)
		ft_dprintf(STDERR_FILENO, "%s\n", STR_PIPE_ERR);
	else if (err == EOF_ERR)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", STR_EOF_ERR, msg);
	else if (err == HEREDOC_ERR)
		ft_dprintf(STDERR_FILENO, "%s (wanted `%s')\n", STR_HERE_ERR, msg);
	else if (err == BAD_FD_ERR)
		ft_dprintf(STDERR_FILENO, "%s %s\n", STR_BAD_FD_ERR, msg);
}
