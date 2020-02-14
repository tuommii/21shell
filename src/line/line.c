/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:10:34 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/14 14:18:12 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_helper2(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

void	get_shell_size(t_line *line)
{
	struct winsize w;

	ioctl(OUTPUT, TIOCGSIZE, &w);
	line->rows = w.ws_row;
	line->cols = w.ws_col;
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

static void debug(t_line *line)
{
	tputs(tgetstr("sc", NULL), 1, &print_helper2);
	tputs(tgetstr("do", NULL), 1, &print_helper2);
	ft_printf("X:[%d], I:[%d], LEN:[%d], COLS: [%d]", line->x, line->i, line->len, line->cols);
	tputs(tgetstr("rc", NULL), 1, &print_helper2);
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
	get_shell_size(line);
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
			//int a = line->len;
			if (line->len + line->prompt_len >  line->cols-1)
			{
				ft_insert(line->input, line->cols-1, '\n');
				ft_putchar('\n');
			}
			if (line->x - line->prompt_len < line->len)
			{
				tputs(tgetstr("im", NULL), 1, &print_helper2);
				tputs(tgetstr("ic", NULL), 1, &print_helper2);
				ft_putchar((char)key);
				tputs(tgetstr("ei", NULL), 1, &print_helper2);
				ft_insert(line->input, line->i + 1, (char)key);
				line->i++;
				line->len++;
				line->x++;
				//debug(line);
				continue;
			}
			else if (line->x - line->prompt_len == line->len)
			{
				line->input[line->i] = (char)key;
			}
			line->delta = line->len - (line->x - line->prompt_len);

			if (line->x == line->cols - 1)
			{
				ft_putstr(tgetstr("do", NULL));
				line->x = 0;
			}
			else {
				line->x++;
			}

			line->len++;
			line->i++;
			ft_putchar((char)key);
		}
		else if (key == BACKSPACE) {
			ft_insert(line->input, line->i, 0);
			if (!line->x)
			{
				ft_putstr(tgetstr("le", NULL));
				ft_putstr(tgetstr("dc", NULL));
				ft_putstr(tgetstr("up", NULL));
				while (line->x < line->cols)
				{
					ft_putstr(tgetstr("nd", NULL));
					line->x++;
				}
				//line->x = line->cols - 1;
				// ft_putstr(tgetstr("nd", NULL));
				// ft_putstr(tgetstr("dc", NULL));
				// ft_putstr(tgetstr("dc", NULL));
				// ft_putstr(tgetstr("le", NULL));
			}
			else {
				ft_putstr(tgetstr("le", NULL));
				ft_putstr(tgetstr("dc", NULL));
			}
			line->len--;
			line->i--;
			line->x--;
		}
		else if (key == ENTER) {
			// Debugging
			ft_printf("\n%s", line->input);

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
		}
		else if (key == RIGHT) {
			ft_putstr(tgetstr("nd", NULL));
			line->i++;
			line->x++;
		}
		//debug(line);
	}

}
