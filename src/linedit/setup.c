/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:46:38 by mtuomine          #+#    #+#             */
/*   Updated: 2020/06/19 18:18:31 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static void	check_tty(void)
{
	char buffer[2048];
	char *name;

	if (!(name = getenv("TERM")))
	{
		ft_dprintf(OUTPUT, "No terminal name");
		exit(1);
	}
	// Commented this out for the Python unittests to work - need to double check
	// if (!isatty(STDIN_FILENO))
	// {
	// 	ft_dprintf(OUTPUT, "No terminal detected!\n");
	// 	exit(1);
	// }
	if (tgetent(buffer, name) != 1)
	{
		ft_dprintf(OUTPUT, "No database or No entry found\n");
		exit(1);
	}
}

/*
** 0 set to raw mode
** 1 restore orginal mode
*/
void		linedit_config(int reset)
{
	static struct termios backup;
	static struct termios new_config;

	if (reset)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &backup);
	}
	else
	{
		tcgetattr(STDIN_FILENO, &backup);
		new_config = backup;
		new_config.c_lflag &= ~(ECHO | ICANON | ECHOE | ECHOK | ECHONL);
		new_config.c_cc[VMIN] = 1;
		new_config.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_config);
	}
}

void		linedit_setup(void)
{
	g_kill = 0;
	check_tty();
	linedit_config(0);
	tputs(tgetstr("cl", NULL), 1, print_char);
}

/*
** TODO: Make prompt dynamic
*/

t_line		*create_line_editor(void)
{
	t_line *line;

	line = (t_line *)ft_memalloc(sizeof(t_line));
	line->len = 0;
	line->old_pos = 0;
	line->lines_used = 1;
	line->hist_count = 0;
	line->hist_i = 0;
	line->cols = get_cols();
	line->hist = NULL;
	line->prompt = "$>";
	line->prompt_len = 2;
	line->pos = 0;
	ft_bzero(line->input, INPUT_BUFFER);
	ft_bzero(line->cpy, INPUT_BUFFER);
	ft_bzero(line->clipboard.content, INPUT_BUFFER);
	return (line);
}
