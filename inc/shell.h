/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 20:30:28 by mtuomine         ###   ########.fr       */
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
# define KEYBOARD_BUFF_LEN 4

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
				// Prompt data
				char *username;
				char *extra;
				int prompt_len;
				int username_len;
				int extra_len;
}				t_shell;

t_shell *create_shell();


/*
** KEYBOARD
*/
int	keypress(void);
int process_key(int code, t_shell *sh);

/*
** PROMPT
*/
void		startup_banner(void);
void		print_prompt(t_shell *sh);

/*
** SETUP
*/
void	config_terminal(int reset);
void	check_tty(void);
int		print_char(int c);

void	listen_signals(void);
void	watch_kill();

/*
** MOVE
*/
void move_left(t_shell *sh);
void move_right(t_shell *sh);

#endif
