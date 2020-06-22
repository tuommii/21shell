/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:27:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/06/22 11:03:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

int		keypress(void)
{
	int		i;
	int		code;
	char	seq[KEYBOARD_BUFFER + 1];

	ft_bzero(seq, KEYBOARD_BUFFER);
	read(STDIN_FILENO, &seq, KEYBOARD_BUFFER);
	seq[KEYBOARD_BUFFER] = '\0';
	i = 0;
	code = 0;
	while (seq[i])
	{
		code += seq[i];
		i++;
	}
	return (code);
}

void	free_history(t_hist **hist)
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

int		print_char(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

int		get_cols(void)
{
	struct winsize w;

	ioctl(OUTPUT, TIOCGSIZE, &w);
	if (w.ws_col <= 0)
		return (80);
	return (w.ws_col);
}

void	erase_input(t_line *line)
{
	ft_bzero(line->input, INPUT_BUFFER);
	line->pos = 0;
	line->len = 0;
	line->lines_used = 1;
}
