/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 20:00:35 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/19 06:10:58 by mtuomine         ###   ########.fr       */
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
	if (sh->len + sh->prompt_len > sh->x)
	{
		sh->x++;
		sh->i++;
		CURSOR_RIGHT(1);
	}
}
