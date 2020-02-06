/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:10:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/06 07:54:22 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void prompt() {
	ft_printf("%-*s", 2, "$>");
}

void start_line_editor() {
	prompt();
	char input[INPUT_BUFFER];
	ft_bzero(input, INPUT_BUFFER);
	int x = 0;
	int len = 0;
	while (1) {
		listen_signals();
		watch_kill();
		int key = keypress();
		if (key == ESC)
		{
			return ;
		}
		else if (ft_isprint(key)) {
			// ft_putchar(key);
			len++;
			ft_putchar(key);
			input[x] = (char)key;
			// ft_insert(input, x, (char)key);
			x++;
		}
		else if (key == ENTER) {
			ft_printf(input);
			ft_putstr(tgetstr("do", NULL));
			ft_bzero(input, INPUT_BUFFER);
			x = 0;
			prompt();
		}
		else if (key == LEFT) {
			move_left();
		}
		else if (key == RIGHT) {
			move_right();
		}
		// ft_putstr(input);
	}

}
