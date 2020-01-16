/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 11:55:04 by mtuomine         ###   ########.fr       */
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

int	main(int argc, char **argv, char **environment)
{
	// TODO: Needs check if space available
	init(argc, argv, environment);
	t_input *input = create_input();
	int code = 0;
	while (1)
	{
		print_prompt(input);
		listen_signals();
		// print_debug(input);
		while ((code = keypress()) != ENTER)
		{
			watch_kill();
			if (ft_isprint(code))
			{
				input->value[input->i] = (char)code;
				ft_printf("%c", input->value[input->i]);
				input->i++;
				input->x++;
				input->len++;
			}
			else if (code == LEFT)
			{
				// ft_printf("DASADSDSA");
				if (input->x > input->prompt_len)
				{
					input->x--;
					ft_printf(tgoto(CM, input->x-1, input->y));
					// continue ;
					//ft_dprintf(0, tgoto(CM, input->x, input->y));
				}
				// t_printf("dsadsadas");
			}
			if (code == ESC)
			{
				ft_printf("\n");
				return (0) ;
			}
		}
		input->y++;
		input->i = 0;
		input->x = input->prompt_len;
		ft_printf("\t[%s]", input->value);
		ft_bzero(input->value, INPUT_BUFFER);
	}
	cleanup(input);
}
