/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:33:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/15 12:13:49 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

void hello(const char *s, t_suggestions *arr)
{
	if (arr)
	{

	}

	ft_printf("%s\n", s);
}

int	main(int argc, char **argv, char **environment)
{
	char *input;
	t_line *line;

	if (!argc || !argv || !environment)
	{
		return (1);
	}

	line = create_line_editor();
	linedit_completion_cb(line, &hello);
	while ((input = linedit(line)) != NULL)
	{
		ft_printf("input: [%s]\n", input);
	}
	free_history(&line->hist);
	ft_bzero(line->input, INPUT_BUFFER);
	ft_bzero(line->clipboard, INPUT_BUFFER);
	ft_bzero(line->debug, INPUT_BUFFER);
	free(line);
	exit(EXIT_SUCCESS);
	return (0);
}
