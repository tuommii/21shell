/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 20:00:35 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/23 14:43:11 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// TODO: Use tgetstr for better support ?

void move_left(t_shell *sh)
{
	if (sh->x > sh->prompt_len)
	{
		sh->x--;
		CURSOR_LEFT(1);
		sh->i--;
	}
}

void move_right(t_shell *sh)
{
	static int new_row = 0;
	if (!new_row)
		new_row += sh->cols;
	if (sh->len + sh->prompt_len + 4 > new_row)
	{
		ft_printf(tgetstr("do", NULL));
		new_row += sh->cols;
	}
	else if (sh->len + sh->prompt_len > sh->x)
	{
		sh->x++;
		sh->i++;
		CURSOR_RIGHT(1);
	}
}
