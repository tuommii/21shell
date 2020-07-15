/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/15 17:01:00 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

static int	which_context(t_completer *ac)
{
	if ((ft_strcmp(ac->ctx, CTX_EXEC)) == 0)
	{
		filter(ac, ac->execs, ac->execs_count);
		return (0);
	}
	else if ((ft_strcmp(ac->ctx, CTX_ENV)) == 0)
	{
		filter(ac, ac->envs, ac->envs_count);
		return (0);
	}
	else if ((ft_strcmp(ac->ctx, CTX_PATH)) == 0)
	{
		filter(ac, ac->paths, ac->paths_count);
		return (0);
	}
	free(ac->word);
	free(ac->ctx);
	return (1);
}

static int	check_errors(t_line *line)
{
	if (!(line->ac->ctx = get_context(line->input, line->pos)))
	{
		free(line->ac->word);
		return (1);
	}
	if (!(line->ac->word = get_word_at(line->input, line->pos)))
	{
		clean_ctx_word(line->ac);
		return (1);
	}
	if (!line->ac->word[0])
	{
		clean_ctx_word(line->ac);
		return (1);
	}
	return (0);
}

/*
** Called when tab is pressed
*/

int			handle_autocomplete(t_line *line)
{
	if (line->readmore)
		return (1);
	if (check_errors(line))
		return (1);
	if (which_context(line->ac))
		return (1);
	if (line->ac->matches_count == 0)
	{
		clean_ctx_word(line->ac);
		tputs(tgetstr("vb", NULL), 1, &print_char);
		return (1);
	}
	sort_by_length(line->ac);
	delete_word(line, line->ac->word);
	insert_word(line, line->ac->matches[0]);
	ac_clean_matches(line->ac);
	clean_ctx_word(line->ac);
	redraw_input(line);
	return (1);
}

t_completer	*create_completer(void)
{
	t_completer	*ac;
	int			i;

	ac = NULL;
	if (!(ac = malloc(sizeof(t_completer))))
		return (NULL);
	i = 0;
	while (i < MAX_MATCHES)
	{
		ac->matches[i] = NULL;
		i++;
	}
	ac->ctx = NULL;
	ac->word = NULL;
	ac->execs_count = 0;
	ac->matches_count = 0;
	ac->envs_count = 0;
	ac->execs = NULL;
	ac->envs = NULL;
	ac->paths = NULL;
	return (ac);
}
