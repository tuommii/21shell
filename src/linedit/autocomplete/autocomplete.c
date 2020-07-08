/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/08 15:11:44 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// complete word based on current word
// static void autocomplete(t_line *line, t_completer *ac)
// {
// 	if (!(ac->word = get_word_at(line->input, line->pos)))
// 	{
// 		ac_clean_suggestions(ac);
// 		free(ac->ctx);
// 		free(ac);
// 		return ;
// 	}
// 	ft_printf("\n%s\n", ac->word);
// 	// after this, matches and matches_count is available
// 	filter(ac);

// 	if (!ac->matches_count)
// 	{
// 		tputs(tgetstr("vb", NULL), 1, &print_char);
// 		ac_clean_rest(ac);
// 		return ;
// 	}
// 	sort_by_length(ac);
// 	delete_word(line, ac->word);
// 	// Shortest is first
// 	insert_word(line, ac->matches[0]);
// 	ac_clean(ac);
// }

// called when tab is pressed
void handle_autocomplete(t_line *line)
{

	// ac = NULL;
	// if (!(ac = malloc(sizeof(t_completer))))
	// 	return ;

	// ac->len = 0;
	// ac->word = NULL;
	// ac->matches_count = 0;
	// ac->ctx = NULL;
	// ac->suggestions = NULL;
	// ac->count = 0;
	if (!(line->ac->ctx = get_context(line->input, line->pos)))
		return ;

	if (!(line->ac->word = get_word_at(line->input, line->pos)))
	{
		free(line->ac->ctx);
		return ;
	}

	if(!line->ac->word[0])
	{
		free(line->ac->word);
		free(line->ac->ctx);
		return ;
	}

	//ft_printf("\nWORD: %s\n", line->ac->word);

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
		return ;
	}
	//ft_printf("\nafter filter: %s\n", line->ac->word);

	if (line->ac->matches_count == 0)
	{
		tputs(tgetstr("vb", NULL), 1, &print_char);
		return ;
	}

	sort_by_length(line->ac);
	delete_word(line, line->ac->word);
	insert_word(line, line->ac->matches[0]);
	ac_clean_matches(line->ac);
	// ac_clean_rest(ac);
	// ac_clean(ac);

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
