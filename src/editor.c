/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:19:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 23:41:48 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// static void insert_middle(char *str, int index, char c)
// {
// }

t_editor *create_editor(void)
{
	t_editor *cursor;

	cursor = (t_editor *)ft_memalloc(sizeof(t_editor));
	cursor->i = 0;
	cursor->x = 0;
	cursor->y = 13;
	ft_bzero(cursor->input, INPUT_BUFFER);
	return (cursor);
}
