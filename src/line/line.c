/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:10:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/10 10:27:55 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void prompt(char *input) {
	ft_printf("%-*s", 2, "$>");
	ft_putstr(tgetstr("sc", NULL));
}

void start_line_editor() {
	char input[INPUT_BUFFER];
	ft_bzero(input, INPUT_BUFFER);
	prompt(input);

	int prompt_len = 2;
	int x = prompt_len;
	int len = 0;
	int i = 0;

	while (1) {
		listen_signals();
		watch_kill();

		int j = 0;

		ft_putstr(tgetstr("rc", NULL));
		while (j < len) {
			ft_putchar(input[j]);
			j++;
		}
		int key = keypress();
		if (key == ESC)
		{
			return ;
		}
		else if (ft_isprint(key)) {
			// ft_putchar(key);
			if ((x - prompt_len) < prompt_len)
			{
				ft_insert(input, x - prompt_len + 1, (char)key);
			}
			else if (x - prompt_len == len)
			{
				input[i] = (char)key;
				i++;
			}
			len++;
			// ft_putchar(key);
			// ft_insert(input, x, (char)key);
			x++;
		}
		else if (key == ENTER) {
			//ft_printf("\tINPUT: %s\n", input);
			ft_putstr(tgetstr("do", NULL));
			ft_bzero(input, INPUT_BUFFER);
			x = prompt_len;
			len = 0;
			i = 0;
			prompt(input);
		}
		else if (key == LEFT) {
			if (x > prompt_len) {
				move_left();
				x--;
			}
		}
		else if (key == RIGHT) {
			move_right();
			x++;
		}
	}

}
