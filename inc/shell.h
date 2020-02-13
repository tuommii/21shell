/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 17:17:05 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <term.h>
# include <unistd.h>
// # include <termios.h>
// # include <termio.h>

# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"

# define OUTPUT STDOUT_FILENO

# define MALLOC_ERROR 2
# define FORK_ERROR 3
# define EXECVE_ERROR 4

/*
** KEYBOARD
*/
# define INPUT_BUFFER 4096
# define KEYBOARD_BUFFER 6

# define TAB 9
# define ENTER 10
# define ESC 27
# define LEFT 186
# define UP 183
# define RIGHT 185
# define DOWN 184
# define BACKSPACE 127
# define DELETE 295

# define CTRL_D 4
# define CTRL_L 12
# define CTRL_LEFT 347
# define CTRL_RIGHT 346
# define CTRL_DOWN 345
# define CTRL_UP 344

# define HOME_KEY 190
# define END_KEY 188

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

/*
** LINUX SUPPORT
*/
# ifndef TIOCGSIZE
#  define TIOCGSIZE TIOCGWINSZ
# endif

/*
** CURSOR MOTION
** Maybe we should use something with tgetstr?
*/
# define CURSOR_RIGHT(x) ft_printf("\033[%dC", (x))
# define CURSOR_LEFT(x) ft_printf("\033[%dD", (x))
# define ERASE_TO_EOL ft_printf("\033[K")
// #define CURSOR(x, y) ft_printf("\033[%d;%df%-s\033", sh->rows, sh->cols, sh->input);


int g_kill;

typedef struct	s_shell
{
				char input[INPUT_BUFFER];
				char **env;
				// Cursor
				int x;
				int y;
				// Index
				int i;
				// sh len
				int len;
				// terminal columns & rows
				int rows;
				int cols;
				// Prompt data
				char *username;
				char *extra;
				int prompt_len;
				int username_len;
				int extra_len;
				// Key pressed
				int key;

				// History data
				struct s_hist *hist;
				int hist_i;
				int hist_count;
}				t_shell;

typedef struct	s_hist
{
	char			*str;
	int				i;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

/*
**	Globals
*/

t_shell			g_sh;

/*
** UTILITIES
*/
void 	cleanup(void);
void 	setup(int argc, char **argv, char **environment);
void	create_shell(char **environ);
void 	reset_shell(void);
void	print_debug(void);
void	parser_debug(t_ast *ast);
void	lexer_debug(t_lexer *lexer);
void 	array_debug(char **arr);
void	ast_debug(t_ast *root, int ws);


/*
** HISTORY
*/
int	hist_append(t_hist **head, char *str);
void hist_print(t_hist *node);
t_hist *hist_pop(t_hist **head, int index);


/*
** KEYBOARD
*/
int	keypress(void);
int which_key(void);
int handle_printable(void);
int handle_arrow_keys(void);
int handle_command_keys(void);


/*
** PROMPT
*/
void		ascii_art(void);
void		print_prompt(void);
void		print_debug(void);
void		print_input(void);
void		get_shell_size(void);


/*
** SETUP
*/
void	config_terminal(int reset);
void	check_tty(void);


void	listen_signals(void);
void	watch_kill();

/*
** MOVE
*/
void move_left(void);
void move_right(void);

/*
** EDIT
*/
void end_of_input(void);
void start_of_input(void);
void erase_input(void);


int		print_char(int c);

/*
** ERROR
*/

void	exit_error(int errno);

#endif
