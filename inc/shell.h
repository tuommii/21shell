/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/31 15:03:50 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <sys/wait.h>
# include <errno.h>

# include "libft.h"
# include "linedit.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"

# define OUTPUT STDOUT_FILENO
# define PASS (void)0

# define MALLOC_ERROR 2
# define FORK_ERR 3
# define EXECVE_ERROR 4
# define SYNTAX_ERR 5
# define PERMISSION_ERR 6
# define NOT_FOUND_ERR 7
# define NOT_DIR_ERR 8
# define PIPE_ERR 9
# define DUP_ERR 10
# define REDIR_ERR 11
# define AMB_REDIR 12

/*
** Definitions of termcaps tuples:
**  CM: cursor motion
**  CL: clear screen
**  CE: clear line
**  VI: invisible cursor
**  VE: visible cursor
**  TI: full screen
**  TE: return to normal mode
*/

# define CM (tgetstr("cm", NULL))
# define CL (tgetstr("cl", NULL))
# define CE (tgetstr("ce", NULL))
# define VI (tgetstr("vi", NULL))
# define VE (tgetstr("ve", NULL))
# define TI (tgetstr("ti", NULL))
# define TE (tgetstr("te", NULL))

int 				g_kill;

typedef struct		s_shell
{
	char			**env;
	struct s_line	*line;
}					t_shell;

/*
**	Globals
*/

t_shell				g_sh;

/*
** Functions
*/

int					print_error(int err, char *msg);
void 				cleanup(t_line *line);
void				create_shell(char **environ);
void				print_debug(void);
void				parser_debug(t_ast *ast);
void				lexer_debug(t_lexer *lexer);
void 				array_debug(char **arr);
void				ast_debug(t_ast *root, int ws);
void				exit_error(int err);

#endif
