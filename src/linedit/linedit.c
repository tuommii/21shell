/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 20:20:23 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/26 20:16:59 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

/*
** Depending on cursor position, apppend or insert char and redraw input
*/
void apped_or_insert(t_line *line, char c)
{
	if (line->len >= INPUT_BUFFER)
		return ;
	if (line->pos == line->len)
	{
		line->input[line->pos] = c;
	}
	else
	{
		ft_insert(line->input, line->pos + 1, c);
	}
	line->len++;
	line->pos++;
	redraw_input(line);
}

void hist_next(t_line *line)
{
	if (line->hist && line->hist->prev && line->hist_i < line->hist_count)
	{
		clear_rows(line);
		erase_input(line);
		t_hist *node = hist_pop(&line->hist, line->hist_i);
		ft_strcpy(line->input, node->str);
		line->len = ft_strlen(line->input);
		goto_end(line);
		line->hist_i++;
	}
}


/*
** Scrolls history backwards, empty input when tail is reached
*/
void hist_prev(t_line *line)
{
	if (line->hist_i == 1)
	{
		clear_rows(line);
		erase_input(line);
		line->hist_i--;
		line->pos = 0;
		redraw_input(line);
	}
	if (line->hist_i > 1)
	{
		line->hist_i--;
		clear_rows(line);
		erase_input(line);
		t_hist *node = hist_pop(&line->hist, line->hist_i - 1);
		ft_strcpy(line->input, node->str);
		line->len = ft_strlen(line->input);
		line->pos = line->len;
		redraw_input(line);
	}
}

int which_action(t_line *line)
{
	int ret;

	ret = 0;
	if ((ret = ft_isprint(line->key)))
	{
		apped_or_insert(line, (char)line->key);
	}
	else if ((ret = check_arrow_keys(line)))
		;
	else if ((ret = check_ctrl_arrow_keys(line)))
		;
	else if ((ret = check_copy_paste_del(line)))
		;
	else if (line->key == HOME_KEY)
	{
		goto_begin(line);
		ret = 1;
	}
	else if (line->key == END_KEY)
	{
		goto_end(line);
		ret = 1;
	}
	return (ret);
}

/*
**
** TODO FOR 42sh
**
** Dont add these in history
** !! print last command
** !ls last command where ls is found
** !1 nth command without parameters
** !-3 nth command with parameters
** Save history to file
** CTRL_R incremental search from history
** fc command which opens latest command in editor and runs that
*/
char	*linedit(t_line *line)
{
	print_prompt(line);
	while (1337)
	{
		listen_signals();
		watch_kill(line);
		line->cols = get_cols();
		line->key = keypress();
		if (check_terminating_keys(line))
			return (NULL);
		else if (check_command_keys(line))
		{
			if (line->key == ENTER)
			{
				return line->debug;
			}
			continue ;
		}
		if (which_action(line))
			continue ;
	}
	return (NULL);
}