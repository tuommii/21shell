/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:16:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 17:33:20 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


t_shell *create_shell(void)
{
	t_shell *shell;

	shell = (t_shell *)ft_memalloc(sizeof(t_shell));
	shell->i = 0;
	shell->y = 13;
	shell->len = 0;
	// TODO: If doesn't exist
	shell->username = getenv("LOGNAME");
	shell->username_len = ft_strlen(shell->username);
	shell->extra = "$>";
	shell->extra_len = ft_strlen(shell->extra);
	shell->prompt_len = shell->username_len + shell->extra_len;
	shell->x = shell->prompt_len;
	ft_bzero(shell->input, shell_BUFFER);
	return (shell);
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
