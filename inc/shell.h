/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/05 14:27:06 by srouhe           ###   ########.fr       */
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

# define OUTPUT STDOUT_FILENO


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
** UTILITIES
*/
void cleanup(t_shell *sh);
void 	setup(int argc, char **argv, char **environment);
t_shell *create_shell();
void reset_shell(t_shell *sh);
void	print_debug(t_shell *sh);


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
int which_key(t_shell *sh);
int handle_printable(t_shell *sh);
int handle_arrow_keys(t_shell *sh);
int handle_command_keys(t_shell *sh);


/*
** PROMPT
*/
void		ascii_art(void);
void		print_prompt(t_shell *sh);
void		print_debug(t_shell *sh);
void		print_input(t_shell *sh);
void		get_shell_size(t_shell *sh);


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
void move_left(t_shell *sh);
void move_right(t_shell *sh);

/*
** EDIT
*/
void end_of_input(t_shell *sh);
void start_of_input(t_shell *sh);
void erase_input(t_shell *sh);


int		print_char(int c);

/*
** EXECUTION
*/

void	fire(t_shell *sh);

/*
** ERROR
*/

void	exit_error(t_shell *sh, int errno);

#endif
