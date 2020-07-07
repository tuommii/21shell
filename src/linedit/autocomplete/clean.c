/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:17:21 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 08:24:33 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void ac_clean_suggestions(t_completions *ac)
{
	int i = 0;
	while (i < ac->count)
	{
		free(ac->suggestions[i]);
		ac->suggestions[i] = NULL;
		i++;
	}
	free(ac->suggestions);
}

void ac_clean_rest(t_completions *ac)
{
	free(ac->word);
	free(ac->ctx);
	free(ac);
}

void ac_clean_matches(t_completions *ac)
{
	int i = 0;
	while (i < ac->matches_count)
	{
		free(ac->matches[i]);
		ac->matches[i] = NULL;
		i++;
	}
}

void ac_clean(t_completions *ac)
{
	ac_clean_matches(ac);
	ac_clean_suggestions(ac);
	ac_clean_rest(ac);
}
