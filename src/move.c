/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 20:00:35 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/17 11:19:36 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// TODO: Use tgetstr for better support ?

void move_left(t_shell *sh)
{
	if (sh->x > sh->prompt_len)
	{
		sh->x--;
		ft_putstr("\033[D");
		sh->i--;
	}
}

void move_right(t_shell *sh)
{
	if (sh->len + sh->prompt_len > sh->x)
	{
		sh->x++;
		sh->i++;
		ft_putstr("\033[C");
	}
}
