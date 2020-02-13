/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:10:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 14:21:00 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_helper2(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

static void goto_begin()
{
	tputs(tgetstr("cr", NULL), 1, &print_helper2);
}

static void goto_prompt(t_line *line) {
	goto_begin();
	int len = line->prompt_len;
	while (len--)
	{
		tputs(tgetstr("nd", NULL), 1, &print_helper2);
	}
}

static void prompt(t_line *line) {
	goto_begin();
	ft_printf("%-*s", 2, "$>");
	goto_prompt(line);
	// ft_putstr(tgetstr("sc", NULL));
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
	int offset = 0;
	// TODO: Free memory
	line = create_line_editor();
	ft_bzero(line->input, INPUT_BUFFER);
	prompt(line);
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
			goto_prompt(line);
			ft_printf("%-s", line->input);
		}
		else if (key == BACKSPACE) {
			ft_insert(line->input, line->i, 0);
			ft_putstr(tgetstr("le", NULL));
			ft_putstr(tgetstr("dc", NULL));
			ft_printf("\n%s", line->input);
		}
		else if (key == ENTER) {
			ft_putstr(tgetstr("do", NULL));
			ft_bzero(line->input, INPUT_BUFFER);
			line->x = line->prompt_len;
			line->len = 0;
			line->i = 0;
			prompt(line);
		}
		else if (key == LEFT) {
			ft_putstr(tgetstr("le", NULL));
			line->i--;
			line->x--;
				//move_left(line);
				// i--;
				// line->x--;
		}
		else if (key == RIGHT) {
			ft_putstr(tgetstr("nd", NULL));
			//move_right(line);
			// line->x++;
		}
		//prompt(line);
		// ft_putstr(tgetstr("rc", NULL));
		// print_input(line);

	}

}
