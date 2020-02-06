/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/06 07:06:29 by mtuomine         ###   ########.fr       */
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
# include "keyboard.h"
# include "line.h"

# define OUTPUT STDOUT_FILENO

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
t_shell *create_shell();
void reset_shell(t_shell *sh);


/*
** HISTORY
*/
int	hist_append(t_hist **head, char *str);
void hist_print(t_hist *node);
t_hist *hist_pop(t_hist **head, int index);


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
