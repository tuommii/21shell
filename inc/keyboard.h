/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:26:14 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 23:39:33 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

#include "editor.h"

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

int	keypress(void);
int process_key(int code, t_editor *cur);


#endif
