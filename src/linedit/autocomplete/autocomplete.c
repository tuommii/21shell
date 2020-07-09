/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/09 11:19:58 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

/*
** Called when tab is pressed
*/

void handle_autocomplete(t_line *line)
{
	if (!(line->ac->ctx = get_context(line->input, line->pos)))
	{
		free(line->ac->word);
		return ;
	}

	if (!(line->ac->word = get_word_at(line->input, line->pos)))
	{
		free(line->ac->word);
		free(line->ac->ctx);
		return ;
	}

	if(!line->ac->word[0])
	{
		free(line->ac->word);
		free(line->ac->ctx);
		return ;
	}

	if ((ft_strcmp(line->ac->ctx, CTX_EXEC)) == 0)
	{
		filter(line->ac, line->ac->execs, line->ac->execs_count);
		// ft_printf("\n%s\n", line->ac->execs[0]);
		// ft_printf("\n%s\n", line->ac->envs[0]);
	}
	else if ((ft_strcmp(line->ac->ctx, CTX_ENV)) == 0)
	{
		filter(line->ac, line->ac->envs, line->ac->envs_count);
	}
	else if ((ft_strcmp(line->ac->ctx, CTX_PATH)) == 0)
	{
		filter(line->ac, line->ac->paths, line->ac->paths_count);
	}
	else
	{
		free(line->ac->word);
		free(line->ac->ctx);
		return ;
	}

	if (line->ac->matches_count == 0)
	{
		free(line->ac->word);
		free(line->ac->ctx);
		tputs(tgetstr("vb", NULL), 1, &print_char);
		return ;
	}

	sort_by_length(line->ac);
	delete_word(line, line->ac->word);
	insert_word(line, line->ac->matches[0]);
	ac_clean_matches(line->ac);
	free(line->ac->word);
	free(line->ac->ctx);
	redraw_input(line);
}
