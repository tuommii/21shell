/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 20:20:23 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/10 10:02:38 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"
#include "shell.h"

/*
** Depending on cursor position, apppend or insert char and redraw input
*/

void		apped_or_insert(t_line *line, char c)
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
}

static int	check_others(t_line *line)
{
	if (line->key == HOME_KEY)
	{
		goto_begin(line);
		return (1);
	}
	else if (line->key == END_KEY)
	{
		goto_end(line);
		return (1);
	}
	else if (line->key == CTRL_L)
	{
		ft_putstr("\033[H\033[J");
		redraw_input(line);
		return (1);
	}
	else if (line->key == CTRL_U)
	{
		ft_bzero(line->input, INPUT_BUFFER);
		line->pos = 0;
		line->len = 0;
		redraw_input(line);
		return (1);
	}
	return (0);
}

int			which_action(t_line *line)
{
	int ret;

	ret = 0;
	if ((ret = ft_isprint(line->key)))
	{
		apped_or_insert(line, (char)line->key);
		redraw_input(line);
	}
	else if ((ret = check_arrow_keys(line)))
		;
	else if ((ret = check_ctrl_arrow_keys(line)))
		;
	else if ((ret = check_copy_paste_del(line)))
		;
	else if ((ret = check_others(line)))
		;
	return (ret);
}

static void	handle_enter(t_line *line)
{
	if (*line->input)
	{
		line->hist_count += hist_append(&line->hist, line->input);
		if (line->hist_count > MAX_HISTORY)
			line->hist_count = MAX_HISTORY;
	}
	line->hist_i = 0;
	ft_strcpy(line->cpy, line->input);
	reposition(line);
}

static char *create_copy_str(t_line *line)
{
	int len = ft_strlen(COPY);
	char *new = malloc(sizeof(char) * (line->len + 3));
	new[0] = '\"';
	int i = 1;
	while (i <= line->len)
	{
		new[i] = line->input[i-1];
		i++;
	}
	new[i] = '\"';
	new[i+1] = '\0';
	new = &new[0];
	char s = '"';
	char *replaced = ft_strreplace(new, &s, "\\\"");
	ft_bzero(line->clipboard.content, INPUT_BUFFER);
	ft_strcpy(line->clipboard.content, replaced);
	ft_strdel(&new);
	ft_strdel(&replaced);
	return line->clipboard.content;
}


char		*linedit(t_line *line)
{
	char	cwd[INPUT_BUFFER + 1];

	getcwd(cwd, INPUT_BUFFER);
	load_paths(line->ac, cwd);
	print_prompt(line);
	while (1337)
	{
		watch_kill(line);
		line->cols = get_cols();
		line->key = keypress();
		if (check_terminating_keys(line))
		{
			ft_putendl("");
			return (NULL);
		}
		else if (line->key == ENTER)
		{
			handle_enter(line);
			return (line->cpy);
		}
		else if (check_command_keys(line))
			continue ;
		else if (which_action(line))
			continue ;
		else if(line->key == CTRL_K)
		{
			line->was_copy = 1;
			// Let's just do special parsing for copying
			// copy_to_clipboard(create_copy_str(line));
			char *new = ft_strjoin("echo ", create_copy_str(line));
			char *new2 = ft_strjoin(new, " | clip.exe");  // because windows
			ft_strdel(&new);
			return (new2);
		}
	}
	return (NULL);
}
