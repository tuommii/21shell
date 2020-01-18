/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:11:32 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/18 15:36:34 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void end_of_input(t_shell *sh)
{
	if (sh->i < sh->len)
	{
		CURSOR_RIGHT(sh->len - sh->i);
		sh->x += sh->len - sh->i;
		sh->i = sh->len;
	}
}

void start_of_input(t_shell *sh)
{
	if (sh->len)
	{
		CURSOR_LEFT(sh->len);
		sh->i -= sh->len;
		sh->x -= sh->len;
		sh->len = 0;
	}
}
