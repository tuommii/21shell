/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:12:05 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/22 11:50:23 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*parse_quotes(char *s)
{
	char	quote[2];

	quote[0] = '"';
	quote[1] = '\0';
	return (ft_str_replace(ft_strdup(s), quote, ""));
}

static void		echo(char *arg)
{
	char	*parsed;

	parsed = parse_quotes(arg);
	ft_putstr(parsed);
	free(parsed);
}

/*
**		Builtin echo command.
**		Checks for no newline (-n) flag and parses quotes.
*/

int				echo_builtin(char **args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!args[i])
	{
		ft_putchar('\n');
		return (1);
	}
	if (ft_strequ(args[i], "-n"))
		flag = 1;
	i += flag;
	while (args[i])
	{
		echo(args[i]);
		i++;
		if (args[i])
			ft_putchar(' ');
	}
	if (!flag)
		ft_putchar('\n');
	return (1);
}
