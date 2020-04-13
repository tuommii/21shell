/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 12:24:19 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/13 18:53:34 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Initialize environment variable array
*/

static char	**init_env(char **env)
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

void 		cleanup(t_line *line)
{
	linedit_config(1);
	erase_input(line);
	free_history(&line->hist);
	free(line);
	ft_freestrarr(g_sh.env);
	exit(EXIT_SUCCESS);
}

/*
** Fatal errors
*/

void		exit_error(int err)
{
	err == MALLOC_ERROR ? ft_putendl_fd("21sh: malloc error.", STDERR_FILENO) : PASS;
	err == FORK_ERR ? ft_putendl_fd("21sh: failed to create child process.", STDERR_FILENO) : PASS;
	err == EXECVE_ERROR ? ft_putendl_fd("21sh: execve error.", STDERR_FILENO) : PASS;
	err == DUP_ERR ? ft_putendl_fd("21sh: dup error.", STDERR_FILENO) : PASS;
	err == REDIR_ERR ? ft_putendl_fd("21sh: redirection error.", STDERR_FILENO) : PASS;
	exit(err);
}

/*
** Print non fatal errors
*/

void		print_error(int err, char *msg)
{
	err == SYNTAX_ERR ? ft_dprintf(STDERR_FILENO, "21sh: syntax error near unexpected token `%s'\n", msg) : PASS;
	err == PERMISSION_ERR ? ft_dprintf(STDERR_FILENO, "21sh: permission denied: %s\n", msg) : PASS;
	err == ENOENT ? ft_dprintf(STDERR_FILENO, "21sh: no such file or directory: %s\n", msg) : PASS;
	err == ENOTDIR ? ft_dprintf(STDERR_FILENO, "21sh: not a directory: %s\n", msg) : PASS;
	err == EISDIR ? ft_dprintf(STDERR_FILENO, "21sh: is a directory: %s\n", msg) : PASS;
	err == AMB_REDIR_ERR ? ft_dprintf(STDERR_FILENO, "21sh: ambiguous redirection: %s\n", msg) : PASS;
	err == PIPE_ERR ? ft_dprintf(STDERR_FILENO, "21sh: pipe error\n") : PASS;
	err == EOF_ERR ? ft_dprintf(STDERR_FILENO, "21sh: unexpected EOF while looking for matching `%s'\n", msg) : PASS;
	err == HEREDOC_ERR ? ft_dprintf(STDERR_FILENO, "21sh: warning: here-document delimited by end-of-file (wanted `%s')\n", msg) : PASS;
	err == BAD_FD_ERR ? ft_dprintf(STDERR_FILENO, "21sh: Bad file descriptor: %s\n", msg) : PASS;
}
