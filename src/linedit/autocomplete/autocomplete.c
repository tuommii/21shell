/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 08:26:32 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// get all available suggestions for right context
void set_suggestions(t_line *line, t_completions **comps)
{
	if (suggestions_env(line, comps))
		return ;
	// Example
	char *example[] = {"echo", "echo-example-3", "$HOME", NULL};
	char **pp = example;
	int i = 0;
	(*comps)->suggestions = malloc(sizeof(char *) * 4);
	while (*pp)
	{
		(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
		ft_strcpy((*comps)->suggestions[i], *pp);
		i++;
		pp++;
	}
	(*comps)->count = i;
}


// complete word based on current word
static void autocomplete(t_line *line, t_completions *comps)
{
	set_suggestions(line, &comps);

	if (!(comps->word = get_word_at(line->input, line->pos)))
	{
		ac_clean_suggestions(comps);
		free(comps->ctx);
		free(comps);
		return ;
	}

	// after this, matches and matches_count is available
	filter(comps);

	if (!comps->matches_count)
	{
		ac_clean_suggestions(comps);
		ac_clean_rest(comps);
		return ;
	}
	sort_by_length(comps);
	delete_word(line, comps->word);
	// Shortest is first
	insert_word(line, comps->matches[0]);
	ac_clean(comps);
}

// called when tab is pressed
void handle_autocomplete(t_line *line)
{
	t_completions *comps;

	comps = NULL;
	if (!(comps = malloc(sizeof(t_completions))))
		return ;

	comps->len = 0;
	comps->word = NULL;
	comps->matches_count = 0;
	comps->ctx = NULL;
	comps->suggestions = NULL;
	if (!(comps->ctx = get_context(line->input, line->pos)))
		return ;

	ft_printf("\n%s\n", comps->ctx);

	if (ft_strcmp(comps->ctx, CTX_DISCARD) == 0)
	{
		free(comps->ctx);
		free(comps);
		return ;
	}
	autocomplete(line, comps);
	redraw_input(line);
}
