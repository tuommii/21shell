/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:02:45 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/11 09:19:08 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// TODO: Use tgetstr for better support ?

void move_left()
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
	ft_putstr(tgetstr("le", NULL));
}

void move_right()
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
	ft_putstr(tgetstr("nd", NULL));
		// ft_putstr(tgetstr("nd", NULL));
		// CURSOR_RIGHT(1);
	// sh->x++;
	// sh->i++;
}
