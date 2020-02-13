/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:11:32 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 16:07:27 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*

- Position the Cursor:
  \033[<L>;<C>H
     Or
  \033[<L>;<C>f
  puts the cursor at line L and column C.
- Move the cursor up N lines:
  \033[<N>A
- Move the cursor down N lines:
  \033[<N>B
- Move the cursor forward N columns:
  \033[<N>C
- Move the cursor backward N columns:
  \033[<N>D

- Clear the screen, move to (0,0):
  \033[2J
- Erase to end of line:
  \033[K

- Save cursor position:
  \033[s
- Restore cursor position:
  \033[u
*/

void end_of_input(void)
{
	if (g_sh.i < g_sh.len)
	{
		CURSOR_RIGHT(g_sh.len - g_sh.i);
		g_sh.x += g_sh.len - g_sh.i;
		g_sh.i = g_sh.len;
	}
}

void start_of_input(void)
{
	int delta;

	delta = g_sh.x - g_sh.prompt_len;
	if (g_sh.len && g_sh.i)
	{
		CURSOR_LEFT(delta);
		g_sh.i -= delta;
		g_sh.x -= delta;
		// g_sh.len = 0;
	}
}

void erase_input(void)
{
	ft_bzero(g_sh.input, INPUT_BUFFER);
	end_of_input();
	start_of_input();
	ERASE_TO_EOL;
	g_sh.len = 0;
}
