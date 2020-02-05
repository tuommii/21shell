/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/05 15:50:48 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		parse_tokens(t_lexer **lexer)
{
	// perform checks, like nbr tokens and syntax errors
	if (!lexer || !*lexer || !(*lexer)->count)
		return (0);
	return (1);
}
