/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:27:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/15 10:05:33 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

int is_empty(char *str)
{
	if (!str || !str[0])
		return (1);
	return (0);
}

void free_history(t_hist **hist)
{
	t_hist *temp;
	temp = NULL;
	while (*hist != NULL)
	{
		temp = *hist;
		*hist = (*hist)->next;
		ft_strdel(&temp->str);
		free(temp);
		temp = NULL;
	}
}

// TODO: Muuta setup.c funktion ja ehkä tämän voi poistaa
int		print_char(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

// rivien maara ei ole tarpeellinen?
// default 80
int get_cols(void)
{
	struct winsize w;
	ioctl(OUTPUT, TIOCGSIZE, &w);
	if (w.ws_col <= 0)
		return (80);
	return w.ws_col;
}

void erase_input(t_line *line)
{
	ft_bzero(line->input, INPUT_BUFFER);
	line->pos = 0;
	line->len = 0;
	line->lines_used = 1;
}
