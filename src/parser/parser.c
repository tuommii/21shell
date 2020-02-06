/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/06 22:33:54 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Create list of commands from lexer tokens
*/

t_cmd		*parse_commands(t_lexer *lexer)
{
	(void)lexer;
	return (NULL);
}

/*
**	1 - check lexer
**	2 - check syntax
*/

t_cmd		*parser(t_lexer **lexer)
{
	t_cmd	*cmd;

	if (!lexer || !*lexer || !(*lexer)->count)
		return (NULL);
	else if (check_syntax(*lexer) == PARSER_ERROR)
		return (NULL);
	cmd = parse_commands(*lexer);
	return (cmd);
}
