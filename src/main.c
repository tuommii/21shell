/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:33:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/26 11:01:52 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

int	main(int argc, char **argv, char **environment)
{
	char *input;
	t_line *line;

	if (!argc || !argv || !environment)
	{
		return (1);
	}

	line = create_line_editor();
	while ((input = linedit(line)) != NULL)
	{
		ft_printf("input: [%s]\n", input);
	}
	free_history(&line->hist);
	free(line);
	exit(EXIT_SUCCESS);
}
