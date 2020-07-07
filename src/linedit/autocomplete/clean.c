/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:17:21 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 08:57:06 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void ac_clean_suggestions(t_completer *ac)
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

void ac_clean_rest(t_completer *ac)
{
	free(ac->word);
	free(ac->ctx);
	free(ac);
}

void ac_clean_matches(t_completer *ac)
{
	int i = 0;
	while (i < ac->matches_count)
	{
		free(ac->matches[i]);
		ac->matches[i] = NULL;
		i++;
	}
}

void ac_clean(t_completer *ac)
{
	ac_clean_matches(ac);
	ac_clean_suggestions(ac);
	ac_clean_rest(ac);
}
