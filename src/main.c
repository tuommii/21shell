/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 19:52:00 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(int argc, char **argv, char **environment)
{
	if (!argc || !argv || !environment)
		exit(EXIT_FAILURE);
	g_kill = 0;
	check_terminal_config();
	config_terminal(0);
	tputs(tgetstr("cl", NULL), 1, print_char);

	int		i;
	int		code;
	char	seq[KEYBOARD_BUFF_LEN + 1];
	while (1)
	{
		listen_signals();
		watch_kill();
		ft_bzero(seq, KEYBOARD_BUFF_LEN);
		read(STDIN_FILENO, &seq, KEYBOARD_BUFF_LEN);
		seq[KEYBOARD_BUFF_LEN] = '\0';
		i = 0;
		code = 0;
		while (seq[i])
		{
			code += seq[i];
			i++;
		}
		ft_printf("%d\n", code);
	}
	// ft_printf("DADADADa");
	// while (1)
	// {
	// }
	config_terminal(1);
	exit(EXIT_SUCCESS);
}
