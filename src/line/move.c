/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:02:45 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/11 10:39:44 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// TODO: Use tgetstr for better support ?

void move_left(t_line *line)
{
	// if (sh->x > sh->prompt_len)
	// {
	// 	sh->x--;
	// 	// CURSOR_LEFT(1);
	// 	ft_putstr(tgetstr("le", NULL));
	// 	sh->i--;
	// }
	// ft_printf(tgoto(tgetstr("cm", NULL), 10, sh->y));
	// sh->x--;
	// sh->i--;
	if (line->x > line->prompt_len)
	{
		ft_putstr(tgetstr("le", NULL));
		line->x--;
		line->i--;
	}
}

void move_right(t_line *line)
{
	// TODO: Prevent going over MAX INT
	// static int new_row = 0;
	// if (!new_row)
	// int new_row = sh->cols;
	// if (sh->len + sh->prompt_len > new_row)
	// {
	// 	ft_putstr(tgetstr("do", NULL));
	// 	new_row = 0;
	// 	// sh->x++;
	// }
	// else if (sh->len + sh->prompt_len > sh->x)
	// {
	if (line->len + line->prompt_len > line->x)
	{
		ft_putstr(tgetstr("nd", NULL));
		line->x++;
		line->i++;
	}
		// ft_putstr(tgetstr("nd", NULL));
		// CURSOR_RIGHT(1);
	// sh->x++;
	// sh->i++;
}
