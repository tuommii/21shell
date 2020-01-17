/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:16:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/17 11:47:13 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	keypress(void)
{
	int		i;
	int		code;
	char	seq[KEYBOARD_BUFFER + 1];

	ft_bzero(seq, KEYBOARD_BUFFER);
	read(STDIN_FILENO, &seq, KEYBOARD_BUFFER);
	seq[KEYBOARD_BUFFER] = '\0';
	i = 0;
	code = 0;
	while (seq[i])
	{
		code += seq[i];
		i++;
	}
	return (code);
}

void handle_printable(t_shell *sh)
{
	if (ft_isprint(sh->key))
	{
		if (sh->x - sh->prompt_len < sh->len)
		{
			ft_insert(sh->input, sh->x - sh->prompt_len + 1, (char)sh->key);
		}
		else if (sh->x - sh->prompt_len == sh->len)
		{
			sh->input[sh->i] = (char)sh->key;
		}
		sh->len++;
		move_right(sh);
	}
}
