/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:21:19 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 19:26:17 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

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

# define CM (tgetstr("cm", NULL))

#define cursorforward(x) printf("\033[%dC", (x))
#define cursorbackward(x) printf("\033[%dD", (x))

typedef struct	s_sh
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

t_shell *create_sh();


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
void		prompt_len(t_shell *sh);


int process(int code, t_shell *sh);


#endif
