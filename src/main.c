/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 17:30:57 by mtuomine         ###   ########.fr       */
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

static void cleanup(t_shell *shell)
{
	// TODO: Free fields aldo
	free(shell);
	config_terminal(1);
	return exit(EXIT_SUCCESS);
}


static void reset_shell(t_shell *shell, int code)
{
	if (code == ENTER)
	{
		ft_printf("\t[%s]\n", shell->input);
		shell->y++;
	}
	shell->i = 0;
	shell->x = shell->prompt_len;
	ft_bzero(shell->input, shell_BUFFER);
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
static void print_debug(t_shell *shell)
{
	ft_printf("\033[s");
	ft_printf("\033[1;1f CURSOR: [%d, %d]\033[u", shell->x, shell->y);
	ft_printf("\033[2;1f INDEX: [%d]\033[u", shell->i);
	ft_printf("\033[u");
}

static void loop(t_shell *shell)
{
	int	code;
	while (1)
	{
		listen_signals();
		print_prompt(shell);
		print_debug(shell);
		while ((code = keypress()) != ENTER)
		{
			watch_kill();
			// ft_printf(FT_RESET);
			if (ft_isprint(code))
			{
				shell->input[shell->i] = (char)code;
				ft_printf("%c", shell->input[shell->i]);
				shell->i++;
				shell->x++;
				shell->len++;
			}
			if (code == LEFT)
			{
				shell->x -= 1;
				ft_putstr("\033[D");
			}
			if (code == RIGHT)
			{
				shell->x++;
				ft_putstr("\033[C");
			}
			else if (code == ESC)
			{
				ft_printf("\n");
				return ;
			}
			else if (code == CTRL_L)
			{
				tputs(tgetstr("cl", NULL), 1, print_char);
				shell->y = 0;
				shell->x = shell->prompt_len;
				break ;
			}
			print_debug(shell);
		}
		reset_shell(shell, code);
	}

}

int	main(int argc, char **argv, char **environment)
{
	// TODO: Needs check if space available
	init(argc, argv, environment);
	t_shell *shell = create_shell();
	loop(shell);
	cleanup(shell);
}
