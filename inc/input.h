/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:21:19 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 17:30:39 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# define shell_BUFFER 4096
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

# define CM (tgetstr("cm", NULL))

#define cursorforward(x) printf("\033[%dC", (x))
#define cursorbackward(x) printf("\033[%dD", (x))

typedef struct	s_shell
{
				char input[shell_BUFFER];
				// Cursor
				int x;
				int y;
				// Index
				int i;
				// shell len
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
int process_key(int code, t_shell *shell);

/*
** PROMPT
*/

void		startup_banner(void);
void		print_prompt(t_shell *shell);
void		prompt_len(t_shell *shell);


int process(int code, t_shell *shell);


#endif
