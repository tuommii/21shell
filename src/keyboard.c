/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:16:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 23:41:13 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	keypress(void)
{
	int		i;
	int		code;
	char	seq[KEYBOARD_BUFF_LEN + 1];

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
	return (code);
}

static int	greater(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}


int process_key(int code, t_editor *cur)
{
	if (code == TAB)
	{
		// ft_printf("AUTOCOMPLETE COMING...\n");
	}

	else if (code == ENTER)
	{
		cur->input[greater(cur->i, cur->x)] = '\0';
		// ft_printf("\nSAMI WILL PARSE THIS...\n");
		ft_printf("\nVALUE WAS: [%s]\n", cur->input);
		ft_bzero(cur->input, 4096);
		// input[0] = '\0';
		cur->i = 0;
		cur->x = 0;
		ft_printf("\n");
		cur->y+=3;
	}

	else if (code == CTRL_L)
	{
		tputs(tgetstr("cl", NULL), 1, print_char);
		cur->y = 0;
		cur->x = 0;
	}

	else if (code == ESC)
	{
		ft_printf("\nSHELL IS TOO AWESOME TO EXIT!\n");
	}

	else if (code == LEFT)
	{
		// ft_printf("\nLEFT\n");
		if (cur->x > 0)
		{
			cur->x--;
		}
		ft_dprintf(0, tgoto(CM, cur->x, cur->y));
	}

	else if (ft_isprint(code))
	{
		if (cur->i == cur->x)
		{
			cur->input[cur->i] = (char)code;
		}
		else
		{
			// insert_middle(cur->input, cur->x, code);
			cur->input[cur->x] = (char)code;
		}
		ft_printf("%c", cur->input[cur->i]);
		cur->i++;
		cur->x++;
	}
	return (0);
}
