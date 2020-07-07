/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 10:36:23 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 22:32:41 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static void	handle_enter_readmore(t_line *line, int nl_flag)
{
	if (*line->input)
	{
		line->hist_count += hist_append(&line->hist, line->input);
		if (line->hist_count > MAX_HISTORY)
			line->hist_count = MAX_HISTORY;
	}
	line->hist_i = 0;
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
	// ft_bzero(line->prompt, INPUT_BUFFER);
	// ft_strcpy(line->prompt, ">");
	// line->prompt_len = ft_strlen(line->prompt);
	// ft_putstr(FT_GREEN);
	// ft_putstr(line->prompt);
	// ft_putstr(FT_RESET);


	line->readmore = 1;
	print_prompt(line);
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
			handle_enter_readmore(line, nl_flag);
			toggle_raw(1, 0);
			return (ft_strdup(line->cpy));
		}
		else if (check_command_keys(line))
			continue ;
		else if (which_action(line))
			continue ;
	}
}
