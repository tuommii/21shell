/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 10:36:23 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/11 20:08:15 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static void	append_to_hist(t_line *line, int nl_flag)
{
	ft_strcpy(line->cpy, line->input);
	if (nl_flag)
		ft_strncat(line->cpy, "\n", 1);
	ft_putstr("\n\r");
	erase_input(line);
}

/*
** nl_fag is for whether to return newlines as well (should be returned always)
*/

char		*read_more(t_line *line, int nl_flag)
{
	toggle_raw(0, 0);
	line->readmore = 1;
	print_prompt(line, NULL, NULL);
	while (42)
	{
		line->cols = get_cols();
		line->key = keypress();
		if (line->key == CTRL_D)
		{
			reposition(line);
			reposition(line);
			return (NULL);
		}
		if (line->key == ENTER)
		{
			append_to_hist(line, nl_flag);
			toggle_raw(1, 0);
			return (ft_strdup(line->cpy));
		}
		else if (check_command_keys(line))
			continue ;
		else if (which_action(line))
			continue ;
	}
	return (NULL);
}
