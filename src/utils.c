/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 12:24:19 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 15:41:15 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Cleanup on exit
*/

void 		cleanup(t_line *line)
{
	linedit_config(1);
	free_history(&line->hist);
	free(line);
	exit(EXIT_SUCCESS);
}

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

void		create_shell(char **environ)
{
	g_sh.env = init_env(environ);
}

/*
** Fatal errors
*/

void		exit_error(int err)
{
	err == MALLOC_ERROR ? ft_putendl("21sh: malloc error.") : PASS;
	err == FORK_ERR ? ft_putendl("21sh: failed to create child process.") : PASS;
	err == EXECVE_ERROR ? ft_putendl("21sh: execve error.") : PASS;
	err == DUP_ERR ? ft_putendl("21sh: dup error.") : PASS;
	err == REDIR_ERR ? ft_putendl("21sh: redirection error.") : PASS;
	exit(err);
}

/*
** Print non fatal errors
*/

int			print_error(int err, char *msg)
{
	err == SYNTAX_ERR ? ft_printf("21sh: syntax error near unexpected token `%s'\n", msg) : PASS;
	err == PERMISSION_ERR || EACCES ? ft_printf("21sh: permission denied: %s\n", msg) : PASS;
	err == ENOENT ? ft_printf("21sh: no such file or directory: %s\n", msg) : PASS;
	err == ENOTDIR ? ft_printf("21sh: not a directory: %s\n", msg): PASS;
	err == EISDIR ? ft_printf("21sh: is a directory: %s\n", msg): PASS;
	err == AMB_REDIR_ERR ? ft_printf("21sh: ambiguous redirection\n"): PASS;
	err == PIPE_ERR ? ft_printf("21sh: pipe error\n"): PASS;
	return (-1);
}
