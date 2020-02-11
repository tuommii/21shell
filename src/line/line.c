/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:10:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/11 11:21:23 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void prompt() {
	ft_printf("%-*s", 2, "$>");
	ft_putstr(tgetstr("sc", NULL));
}

static void print_input(t_line *line) {
	ft_putstr(tgetstr("rc", NULL));
	ft_printf("%-*s", line->len, line->input);
}

static t_line *create_line_editor(void)
{
	t_line *line;

	// TODO: Check malloc
	line = (t_line *)ft_memalloc(sizeof(t_line));
	line->i = 0;
	// TODO: Make this dynamic
	line->prompt_len = 2;
	line->x = line->prompt_len;
	line->len = 0;
	line->delta = 0;
	return (line);
}

void start_line_editor() {
	t_line *line;

	// TODO: Free memory
	line = create_line_editor();
	ft_bzero(line->input, INPUT_BUFFER);
	prompt();

	while (1) {
		listen_signals();
		watch_kill();
		int key = keypress();
		if (key == ESC)
		{
			return ;
		}
		else if (ft_isprint(key)) {
			if (line->x - line->prompt_len < line->len)
			{
				ft_insert(line->input, line->x - line->prompt_len + 1, (char)key);
			}
			else if (line->x - line->prompt_len == line->len)
			{
				line->input[line->i] = (char)key;
			}
			line->delta = line->len - (line->x - line->prompt_len);
			line->len++;
			line->x++;
			line->i++;

			print_input(line);

				// move_left(line);

		}
		else if (key == BACKSPACE) {
			ft_insert(line->input, line->i, 0);
			print_input(line);
			move_left(line);
			// FIX CURSOR GOING END
			if (line->len > 0)
				line->len--;
			continue;
		}
		else if (key == ENTER) {
			ft_putstr(tgetstr("do", NULL));
			ft_bzero(line->input, INPUT_BUFFER);
			line->x = line->prompt_len;
			line->len = 0;
			line->i = 0;
			prompt();
		}
		else if (key == LEFT) {
				move_left(line);
				// i--;
				// line->x--;
		}
		else if (key == RIGHT) {
			move_right(line);
			// line->x++;
		}
		while (line->delta-- > 0)
			ft_putstr(tgetstr("le", NULL));
	}

}
