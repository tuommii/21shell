/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:16:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 16:26:04 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


t_input *create_input(void)
{
	t_input *input;

	input = (t_input *)ft_memalloc(sizeof(t_input));
	input->i = 0;
	input->y = 13;
	input->len = 0;
	// TODO: If doesn't exist
	input->username = getenv("LOGNAME");
	input->username_len = ft_strlen(input->username);
	input->extra = "$>";
	input->extra_len = ft_strlen(input->extra);
	input->prompt_len = input->username_len + input->extra_len;
	input->x = input->prompt_len;
	ft_bzero(input->value, INPUT_BUFFER);
	return (input);
}

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

int process(int code, t_input *input)
{
	while (code != ENTER)
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
			}
		}
		if (code == ESC)
		{
			ft_printf("\n");
			return (-1) ;
		}
	}
	return (0);
}


int process_key(int code, t_input *input)
{
	if (ft_isprint(code))
	{

		input->value[input->i] = (char)code;
		ft_printf("%c", input->value[input->i]);
		input->i++;
		input->x++;
		input->len++;
	}
	if (code == TAB)
	{
		// ft_printf("AUTOCOMPLETE COMING...\n");
	}

	else if (code == ENTER)
	{
		input->value[input->i] = '\0';
		ft_printf("\nVALUE WAS: [%s]\n", input->value);
		ft_bzero(input->value, 4096);
		input->i = 0;
		input->x = input->prompt_len;
		input->y+=3;
		ft_printf("\n");
		return (-10);
	}

	else if (code == ESC)
	{
		ft_printf("\nSHELL IS TOO AWESOME TO EXIT!\n");
	}

	else if (code == LEFT)
	{
		if (input->x > input->prompt_len - 1)
		{
			input->x--;
		}
		ft_dprintf(0, tgoto(CM, input->x, input->y));
		return (-2);
	}

	else if (code == RIGHT)
	{
		if (input->x < input->len)
		{
			input->x++;
		}
		ft_dprintf(0, tgoto(CM, input->x, input->y));
	}

	// TODO: Delete middle
	else if (code == BACKSPACE || code == DELETE)
	{

	}
	return (0);
}
