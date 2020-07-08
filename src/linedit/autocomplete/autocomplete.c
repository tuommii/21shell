/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/08 09:14:18 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// get all available suggestions for right context
void set_suggestions(t_line *line, t_completer **ac)
{
	int j = 0;
	char **cpy = line->execs;
	while(*cpy != NULL)
	{
		cpy++;
		j++;
	}

	(*ac)->suggestions = NULL;

	if (suggestions_env(line, ac))
		return ;

	// if (!((*ac)->suggestions = get_execs(line->envs)))
	// {
	// 	ft_printf("\nPROBLEM\n");
	// 	return ;
	// }
	// (*ac)->count = j;
}


// complete word based on current word
static void autocomplete(t_line *line, t_completer *ac)
{
	set_suggestions(line, &ac);

	if (!(ac->word = get_word_at(line->input, line->pos)))
	{
		ac_clean_suggestions(ac);
		free(ac->ctx);
		free(ac);
		return ;
	}

	// ft_printf("\nCOUNT: %d\n", ac->count);

	// after this, matches and matches_count is available
	filter(ac);

	if (!ac->matches_count)
	{
		tputs(tgetstr("vb", NULL), 1, &print_char);
		ac_clean_suggestions(ac);
		ac_clean_rest(ac);
		return ;
	}
	sort_by_length(ac);
	delete_word(line, ac->word);
	// Shortest is first
	insert_word(line, ac->matches[0]);
	ac_clean(ac);
}

// called when tab is pressed
void handle_autocomplete(t_line *line)
{
	t_completer *ac;

	// ac = NULL;
	// if (!(ac = malloc(sizeof(t_completer))))
	// 	return ;

	// ac->len = 0;
	// ac->word = NULL;
	// ac->matches_count = 0;
	// ac->ctx = NULL;
	// ac->suggestions = NULL;
	// ac->count = 0;
	ac = line->ac;
	if (!(ac->ctx = get_context(line->input, line->pos)))
		return ;
	if ((ft_strcmp(ac->ctx, CTX_EXEC)) == 0)
	{
		ft_printf("\n%s\n", ac->execs[0]);
		ft_printf("\n%s\n", ac->envs[0]);
	}

	// //ft_printf("\n%s\n", ac->ctx);

	// if (ft_strcmp(ac->ctx, CTX_DISCARD) == 0)
	// {
	// 	free(ac->ctx);
	// 	free(ac);
	// 	return ;
	// }
	// autocomplete(line, ac);
	redraw_input(line);
}
