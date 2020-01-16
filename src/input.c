/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:16:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 20:25:17 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


t_shell *create_shell(void)
{
	t_shell *sh;

	sh = (t_shell *)ft_memalloc(sizeof(t_shell));
	sh->i = 0;
	sh->y = 13;
	sh->len = 0;
	// TODO: If doesn't exist
	sh->username = getenv("LOGNAME");
	sh->username_len = ft_strlen(sh->username);
	sh->extra = "$>";
	sh->extra_len = ft_strlen(sh->extra);
	sh->prompt_len = sh->username_len + sh->extra_len;
	sh->x = sh->prompt_len;
	ft_bzero(sh->input, INPUT_BUFFER);
	return (sh);
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
