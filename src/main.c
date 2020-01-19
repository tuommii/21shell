/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/19 06:35:38 by mtuomine         ###   ########.fr       */
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

// After ENTER pressed, reset variables
static void reset_shell(t_shell *sh)
{
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


static int read_input(t_shell *sh)
{
	while ((sh->key = keypress()) != ENTER)
	{
		watch_kill();

		which_key(sh);

		print_debug(sh);
		print_input(sh);
	}
	if (sh->input)
		hist_append(&sh->hist, sh->input);

	return (ENTER);
}


static void run_shell(t_shell *sh)
{
	while (1)
	{
		listen_signals();
		print_prompt(sh);
		print_debug(sh);
		if ((sh->key = read_input(sh)) == ESC)
			return ;

		// Sami, sh->input contains input string! Parse that!

		// hist_print(sh->hist);
		if (sh->hist && sh->hist->prev)
			ft_printf("INDEX: %d, LAST: %s", sh->hist->prev->i, sh->hist->prev->str);
		reset_shell(sh);
	}
}

int	main(int argc, char **argv, char **environment)
{
	t_shell *sh;
	setup(argc, argv, environment);
	sh = create_shell();
	run_shell(sh);
	cleanup(sh);
}
