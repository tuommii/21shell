/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/02 10:29:09 by mtuomine         ###   ########.fr       */
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

# define OUTPUT 			STDOUT_FILENO
# define PASS 				(void)0

/*
** Error numbers
*/
# define MALLOC_ERROR		2
# define FORK_ERR			3
# define EXECVE_ERROR		4
# define SYNTAX_ERR			5
# define PERMISSION_ERR 	6
# define NOT_FOUND_ERR		7
# define NOT_DIR_ERR		8
# define PIPE_ERR			9
# define DUP_ERR			10
# define REDIR_ERR			11
# define AMB_REDIR_ERR		12
# define EOF_ERR			14
# define HEREDOC_ERR		15
# define BAD_FD_ERR			16

/*
** Error messages
*/
# define STR_MALLOC_ERR	"21sh: malloc error."
# define STR_FORK_ERR "21sh: failed to create child process."
# define STR_EXECVE_ERR	"21sh: execve error."
# define STR_SYNTAX_ERR	"21sh: syntax error near unexpected token"
# define STR_PERMISSION_ERR	"21sh: permission denied:"
# define STR_NOT_FOUND_ERR "21sh: No such file or directory"
# define STR_NOT_DIR_ERR "21sh: Not a directory"
# define STR_IS_DIR "21sh: is a directory:"
# define STR_PIPE_ERR "21sh: pipe error"
# define STR_DUP_ERR "21sh: dup error."
# define STR_REDIR_ERR "21sh: redirection error."
# define STR_AMB_REDIR_ERR "21sh: ambiguous redirection:"
# define STR_EOF_ERR "21sh: unexpected EOF while looking for matching"
# define STR_HERE_ERR "21sh: warning: here-document delimited by end-of-file"
# define STR_BAD_FD_ERR	"21sh: Bad file descriptor:"

typedef struct			s_shell
{
	int					status;
	char				**env;
	struct s_line		*line;
}						t_shell;

/*
**	Globals
*/

t_shell					g_sh;

/*
** Functions
*/

void					print_error(int err, char *msg);
void					cleanup(t_line *line);
void					create_shell(char **environ, t_line *line);
void					print_debug(void);
void					parser_debug(t_ast *ast);
void					lexer_debug(t_lexer *lexer);
void					array_debug(char **arr);
void					ast_debug(t_ast *root, int ws);
void					exit_error(int err, char *msg);
void					run_21_stdin(void);

#endif
