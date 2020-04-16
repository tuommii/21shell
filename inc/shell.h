/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/04/16 14:23:10 by srouhe           ###   ########.fr       */
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
# define STR_MALLOC_ERR
# define STR_FORK_ERR	
# define STR_EXECVE_ERR	
# define STR_SYNTAX_ERR		
# define STR_PERMISSION_ERR
# define STR_NOT_FOUND_ERR
# define STR_NOT_DIR_ERR	
# define STR_PIPE_ERR		
# define STR_DUP_ERR		
# define STR_REDIR_ERR		
# define STR_AMB_REDIR_ERR	
# define STR_EOF_ERR		
# define STR_HEREDOC_ERR	
# define STR_BAD_FD_ERR		

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

int 					g_kill;

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
void 					cleanup(t_line *line);
void					create_shell(char **environ, t_line *line);
void					print_debug(void);
void					parser_debug(t_ast *ast);
void					lexer_debug(t_lexer *lexer);
void 					array_debug(char **arr);
void					ast_debug(t_ast *root, int ws);
void					exit_error(int err);

#endif
