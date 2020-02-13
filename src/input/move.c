/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 20:00:35 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 16:09:29 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// TODO: Use tgetstr for better support ?

void move_left(void)
{
	if (g_sh.x > g_sh.prompt_len)
	{
		g_sh.x--;
		CURSOR_LEFT(1);
		g_sh.i--;
	}
}

void move_right(void)
{
	static int new_row = 0;
	if (!new_row)
		new_row += g_sh.cols;
	if (g_sh.len + g_sh.prompt_len + 4 > new_row)
	{
		ft_printf(tgetstr("do", NULL));
		new_row += g_sh.cols;
	}
	else if (g_sh.len + g_sh.prompt_len > g_sh.x)
	{
		g_sh.x++;
		g_sh.i++;
		CURSOR_RIGHT(1);
	}
}
