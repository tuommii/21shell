/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:14:51 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/10 13:54:21 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void	insert_word(t_line *line, char *word)
{
	while (*word)
	{
		apped_or_insert(line, *word);
		word++;
	}
}

void	clean_ctx_word(t_completer *ac)
{
	free(ac->word);
	free(ac->ctx);
}

void	ac_clean_rest(t_completer *ac)
{
	clean_ctx_word(ac);
	free(ac);
}

void	ac_clean_matches(t_completer *ac)
{
	int i;

	i = 0;
	while (i < ac->matches_count)
	{
		free(ac->matches[i]);
		ac->matches[i] = NULL;
		i++;
	}
}
