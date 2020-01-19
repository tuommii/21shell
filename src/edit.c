/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:11:32 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/19 11:25:27 by mtuomine         ###   ########.fr       */
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

void end_of_input(t_shell *sh)
{
	if (sh->i < sh->len)
	{
		CURSOR_RIGHT(sh->len - sh->i);
		sh->x += sh->len - sh->i;
		sh->i = sh->len;
	}
}

void start_of_input(t_shell *sh)
{
	if (sh->len)
	{
		CURSOR_LEFT(sh->len);
		sh->i -= sh->len;
		sh->x -= sh->len;
		// sh->len = 0;
	}
}

void erase_input(t_shell *sh)
{
	ft_bzero(sh->input, INPUT_BUFFER);
	end_of_input(sh);
	start_of_input(sh);
	ERASE_TO_EOL;
}
