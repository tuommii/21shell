/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 13:25:21 by mtuomine         ###   ########.fr       */
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

static void loop(t_input *input)
{
	int	code;
	while (1)
	{
		ft_printf("%d, %d, %d\n", input->x, input->y, input->i);
		print_prompt(input);
		listen_signals();
		while ((code = keypress()) != ENTER)
		{
			watch_kill();
			if (ft_isprint(code))
			{
				input->value[input->i] = (char)code;
				ft_printf("%c", input->value[input->i]);
				input->i++;
				// input->x++;
				input->len++;
			}
			if (code == LEFT)
			{
				input->i = '\0';
				// ft_printf("DASADSDSA");
				// if (input->x > input->prompt_len)
				// {
					// input->x--;
					 ft_printf("\033[D");
					// ft_printf(tgoto(CM, input->x-1, input->y));
				// }
			}
			if (code == RIGHT)
			{
				// ft_printf("DASADSDSA");
				if (input->x - input->prompt_len < input->len)
				{
					 ft_printf("\033[C");
					input->x++;
					// ft_printf(tgoto(CM, input->x, input->y));
				}
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
	// int code = 0;
	// while (1)
	// {
	// 	print_prompt(input);
	// 	listen_signals();
	// 	// print_debug(input);
	// 	while ((code = keypress()) != ENTER)
	// 	{
	// 		watch_kill();
	// 		if (ft_isprint(code))
	// 		{
	// 			input->value[input->i] = (char)code;
	// 			ft_printf("%c", input->value[input->i]);
	// 			input->i++;
	// 			input->x++;
	// 			input->len++;
	// 		}
	// 		else if (code == LEFT)
	// 		{
	// 			// ft_printf("DASADSDSA");
	// 			if (input->x > input->prompt_len)
	// 			{
	// 				input->x--;
	// 				ft_printf(tgoto(CM, input->x-1, input->y));
	// 			}
	// 		}
	// 		if (code == ESC)
	// 		{
	// 			ft_printf("\n");
	// 			return (0) ;
	// 		}
	// 	}
	// 	reset_input(input);
	// 	// input->y++;
	// 	// input->i = 0;
	// 	// input->x = input->prompt_len;
	// 	// ft_printf("\t[%s]", input->value);
	// 	// ft_bzero(input->value, INPUT_BUFFER);
	// }
	cleanup(input);
}
