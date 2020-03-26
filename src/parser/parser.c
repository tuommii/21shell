/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 17:55:34 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	1 - check lexer
**	2 - check syntax
*/

int		parser(t_lexer **lexer)
{
	if (!lexer || !*lexer || !(*lexer)->count)
		return (PARSER_ERROR);
	else if (check_syntax(*lexer) == PARSER_ERROR)
		return (PARSER_ERROR);
	return (PARSER_OK);
}
