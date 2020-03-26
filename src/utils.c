/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 12:24:19 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/26 13:12:36 by srouhe           ###   ########.fr       */
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

// free mem also
void		exit_error(int errno)
{
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), OUTPUT);
	errno == MALLOC_ERROR ? ft_putendl("21sh: malloc error.") : PASS;
	errno == FORK_ERR ? ft_putendl("21sh: failed to create child process.") : PASS;
	errno == EXECVE_ERROR ? ft_putendl("21sh: execve error.") : PASS;
	errno == DUP_ERR ? ft_putendl("21sh: dup error.") : PASS;
	errno == REDIR_ERR ? ft_putendl("21sh: redirection error.") : PASS;
	// reset_shell();
	ft_freestrarr(g_sh.env);
	exit(errno);
}

void		print_error(int errno, char *msg)
{
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), OUTPUT);
	errno == SYNTAX_ERR ? ft_printf("21sh: syntax error near unexpected token `%s'", msg) : PASS;
	errno == PERMISSION_ERR ? ft_printf("21sh: permission denied: %s", msg) : PASS;
	errno == NOT_FOUND_ERR ? ft_printf("21sh: no such file or directory: %s", msg) : PASS;
	errno == NOT_DIR_ERR ? ft_printf("21sh: not a directory: %s", msg): PASS;
}