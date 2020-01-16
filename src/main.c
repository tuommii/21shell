/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 21:20:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void cleanup(t_shell *sh)
{
	// TODO: Free fields aldo
	free(sh);
	config_terminal(1);
	return exit(EXIT_SUCCESS);
}


static void reset_shell(t_shell *sh, int code)
{
	if (code == ENTER)
	{
		ft_printf("\t[%s]\n", sh->input);
		sh->y++;
	}
	sh->i = 0;
	sh->x = sh->prompt_len;
	ft_bzero(sh->input, INPUT_BUFFER);
}

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

static int read_input(t_shell *sh)
{
	int code;

	while ((code = keypress()) != ENTER)
	{
		watch_kill();
		if (ft_isprint(code))
		{
			sh->input[sh->i] = (char)code;
			ft_printf("%c", sh->input[sh->i]);
			sh->i++;
			sh->x++;
			sh->len++;
		}
		if (code == LEFT)
			move_left(sh);
		if (code == RIGHT)
			move_right(sh);
		else if (code == ESC)
		{
			ft_printf("\n");
			return (ESC);
		}
		else if (code == CTRL_L)
		{
			tputs(tgetstr("cl", NULL), 1, print_char);
			sh->y = 0;
			sh->x = sh->prompt_len;
			return (CTRL_L) ;
		}
		print_debug(sh);
	}
	return (ENTER);
}


static void loop(t_shell *sh)
{
	int	code = 0;
	while (1)
	{
		listen_signals();
		print_prompt(sh);
		print_debug(sh);
		if ((code = read_input(sh)) == ESC)
			return ;

		// Sami, sh->input contains input string! Parse that!

		reset_shell(sh, code);
	}
}

int	main(int argc, char **argv, char **environment)
{
	// TODO: Needs check if space available
	init_shell(argc, argv, environment);
	t_shell *sh = create_shell();
	loop(sh);
	cleanup(sh);
}
