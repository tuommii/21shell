/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 16:25:41 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void init(int argc, char **argv, char **environment)
{
	if (!argc || !argv || !environment)
		exit(EXIT_FAILURE);
	g_kill = 0;
	check_tty();
	config_terminal(0);
	tputs(tgetstr("cl", NULL), 1, print_char);
	startup_banner();
}

static void cleanup(t_input *input)
{
	// TODO: Free fields aldo
	free(input);
	config_terminal(1);
	return exit(EXIT_SUCCESS);
}


static void reset_input(t_input *input, int code)
{
	if (code == ENTER)
	{
		ft_printf("\t[%s]\n", input->value);
		input->y++;
	}
	input->i = 0;
	input->x = input->prompt_len;
	ft_bzero(input->value, INPUT_BUFFER);
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
static void print_debug(t_input *input)
{
	ft_printf("\033[s");
	ft_printf("\033[1;1f CURSOR: [%d, %d]\033[u", input->x, input->y);
	ft_printf("\033[2;1f INDEX: [%d]\033[u", input->i);
	ft_printf("\033[u");
}

static void loop(t_input *input)
{
	int	code;
	while (1)
	{
		listen_signals();
		print_prompt(input);
		// print_debug(input);
		while ((code = keypress()) != ENTER)
		{
			watch_kill();
			// ft_printf(FT_RESET);
			if (ft_isprint(code))
			{
				input->value[input->i] = (char)code;
				ft_printf("%c", input->value[input->i]);
				input->i++;
				input->x++;
				input->len++;
			}
			if (code == LEFT)
			{
				input->x -= 1;
				ft_printf("\033[D");
			}
			if (code == RIGHT)
			{
				input->x++;
				ft_printf("\033[C");
			}
			else if (code == ESC)
			{
				ft_printf("\n");
				return ;
			}
			else if (code == CTRL_L)
			{
				tputs(tgetstr("cl", NULL), 1, print_char);
				input->y = 0;
				input->x = input->prompt_len;
				break ;
			}
			print_debug(input);
		}
		reset_input(input, code);
	}

}

int	main(int argc, char **argv, char **environment)
{
	// TODO: Needs check if space available
	init(argc, argv, environment);
	t_input *input = create_input();
	loop(input);
	cleanup(input);
}
