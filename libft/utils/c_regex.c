/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_regex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:33:47 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/21 20:39:19 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** search for regexp anywhere in s
*/

int		re_match(char *regexp, char *s)
{
	if (regexp[0] == '^')
		return (matchhere(regexp + 1, s));
	if (matchhere(regexp, s))
		return (1);
	while (*s++)
	{
		if (matchhere(regexp, s))
			return (1);
	}
	return (0);
}

/*
** search for regexp at beginning of s
*/

int		matchhere(char *regexp, char *s)
{
	if (regexp[0] == '\0')
		return (1);
	if (regexp[1] == '*')
		return (matchstar(regexp[0], regexp + 2, s));
	if (regexp[0] == '$' && !regexp[1])
		return (*s == '\0');
	if (*s && (regexp[0] == '.' || regexp[0] == *s))
		return (matchhere(regexp + 1, s + 1));
	return (0);
}

/*
** search for c* regexp at beginning of s
*/

int		matchstar(int c, char *regexp, char *s)
{
	if (matchhere(regexp, s))
		return (1);
	while (*s && (*s++ == c || c == '.'))
	{
		if (matchhere(regexp, s))
			return (1);
	}
	return (0);
}