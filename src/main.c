/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/18 08:12:19 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

 void cleanup(t_shell *sh)
{
	// TODO: Free fields aldo

	free(sh);
	config_terminal(1);
	return exit(EXIT_SUCCESS);
}

// After ENTER pressed, reset variables
 void reset_shell(t_shell *sh)
{
	// Define position for this
	// if (code == ENTER)
	// {
	// 	ft_printf("\t[%s]\n", sh->input);
	// 	sh->y++;
	// }
	if (sh->key == ENTER)
	{
		ft_printf("\n");
	}
	sh->i = 0;
	sh->x = sh->prompt_len;
	sh->y++;
	if (sh->y > sh->rows)
		sh->y = sh->rows;
	sh->len = 0;
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

 int read_input(t_shell *sh)
{

	while ((sh->key = keypress()) != ENTER)
	{
		watch_kill();
		handle_printable(sh);
		if (sh->key == LEFT)
			move_left(sh);
		else if (sh->key == RIGHT)
			move_right(sh);
		else if (sh->key == TAB)
			tputs(tgetstr("vb", NULL), 1, print_char);
		else if (sh->key == BACKSPACE)
		{
			ft_insert(sh->input, sh->i, 0);
			move_left(sh);
			print_input(sh);
			if (sh->len > 0)
				sh->len--;
		}
		else if (sh->key == ESC)
		{
			ft_printf("\n");
			return (ESC);
		}
		else if (sh->key == CTRL_L)
		{
			tputs(tgetstr("cl", NULL), 1, print_char);
			sh->y = -1;
			sh->x = sh->prompt_len;
			return (CTRL_L) ;
		}
		print_debug(sh);
		print_input(sh);
	}
	return (ENTER);
}


 void loop(t_shell *sh)
{
	while (1)
	{
		listen_signals();
		print_prompt(sh);
		print_debug(sh);
		if ((sh->key = read_input(sh)) == ESC)
			return ;

		// Sami, sh->input contains input string! Parse that!

		reset_shell(sh);
	}
}

int	main(int argc, char **argv, char **environment)
{
	// Testing history
	t_hist *hh = NULL;
	hist_append(&hh, "Eka");
	hist_append(&hh, "Toka");
	hist_append(&hh, "Kolmas");
	hist_print(hh);

	if (argc || argv || environment) {}
	// TODO: Needs check if space available
	// init_shell(argc, argv, environment);
	// t_shell *sh = create_shell();
	// loop(sh);
	// cleanup(sh);
}
