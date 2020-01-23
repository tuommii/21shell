/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:56:02 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/23 17:10:17 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define T_S_COL			(1 << 0)
# define T_PIPE				(1 << 1)
# define T_SLARR			(1 << 2)
# define T_SRARR			(1 << 3)
# define T_DLARR			(1 << 4)
# define T_DRARR			(1 << 5)
# define T_STR				(1 << 10)
# define T_NBR				(1 << 11)

# define MASK 0b111111

typedef struct			s_token
{
	int					id;
	char				*s;
	struct s_token		*next;
}						t_token;

void					tokenize(char *input);

#endif
