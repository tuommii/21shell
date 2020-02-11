/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:10:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/11 09:44:22 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void prompt() {
	ft_printf("%-*s", 2, "$>");
	ft_putstr(tgetstr("sc", NULL));
}

void start_line_editor() {
	char input[INPUT_BUFFER];
	ft_bzero(input, INPUT_BUFFER);
	prompt();

	int prompt_len = 2;
	int x = prompt_len;
	int len = 0;
	int i = 0;

	while (1) {
		listen_signals();
		watch_kill();
		int key = keypress();
		if (key == ESC)
		{
			return ;
		}
		else if (ft_isprint(key)) {
			if (x - prompt_len < len)
			{
				ft_insert(input, x - prompt_len + 1, (char)key);
			}
			else if (x - prompt_len == len)
			{
				input[i] = (char)key;
			}
			int delta = len - (x - prompt_len);
			len++;
			x++;
			i++;
			ft_putstr(tgetstr("rc", NULL));
			ft_printf("%-*s", len, input);

			while (delta-- > 0)
				move_left();

		}
		else if (key == ENTER) {
			ft_putstr(tgetstr("do", NULL));
			ft_bzero(input, INPUT_BUFFER);
			x = prompt_len;
			len = 0;
			i = 0;
			prompt();
		}
		else if (key == LEFT) {
				move_left();
				// i--;
				x--;
		}
		else if (key == RIGHT) {
			move_right();
			x++;
		}
	}

}
