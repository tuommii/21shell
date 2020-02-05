/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 20:00:35 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/05 12:02:55 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// TODO: Use tgetstr for better support ?

void move_left(t_shell *sh)
{
	if (sh->x > sh->prompt_len)
	{
		sh->x--;
		// CURSOR_LEFT(1);
		ft_putstr(tgetstr("le", NULL));
		sh->i--;
	}
}

void move_right(t_shell *sh)
{
	// TODO: Prevent going over MAX INT
	static int new_row = 0;
	if (!new_row)
		new_row += sh->cols;
	if (sh->len + sh->prompt_len > new_row)
	{
		ft_putstr(tgetstr("do", NULL));
		new_row += sh->cols;
		// sh->x++;
	}
	else if (sh->len + sh->prompt_len > sh->x)
	{
		ft_putstr(tgetstr("nd", NULL));
		// CURSOR_RIGHT(1);
	}
	sh->x++;
	sh->i++;
}
