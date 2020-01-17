/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/17 18:25:12 by mtuomine         ###   ########.fr       */
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

# include "../libft/libft.h"

# define OUTPUT STDOUT_FILENO


/*
** KEYBOARD
*/
# define INPUT_BUFFER 4096
# define KEYBOARD_BUFFER 4

# define TAB 9
# define ENTER 10
# define CTRL_L 12
# define ESC 27
# define LEFT 186
# define UP 183
# define RIGHT 185
# define DOWN 184
# define BACKSPACE 127
# define DELETE 295

/*
** CURSOR MOTION
*/
#define CURSOR_RIGHT(x) ft_putstr("\033[%dC", (x))
#define CURSOR_LEFT(x) ft_putstr("\033[%dD", (x))
#define CURSOR(x, y) ft_printf("\033[%d;%df%-s\033", sh->rows, sh->cols, sh->input);


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
				int key;
}				t_shell;

// typedef struct	s_hist
// {
// 	char **items;
// 	int	count;
// }				t_hist;

void 	init_shell(int argc, char **argv, char **environment);
t_shell *create_shell();

/*
** KEYBOARD
*/
int	keypress(void);
void handle_printable(t_shell *sh);

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



int		print_char(int c);

#endif
