/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:56:02 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/05 10:15:04 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "shell.h"

# define T_S_COL			(1 << 0)
# define T_PIPE				(1 << 1)
# define T_SLARR			(1 << 2)
# define T_SRARR			(1 << 3)
# define T_DLARR			(1 << 4)
# define T_DRARR			(1 << 5)
# define T_STR				(1 << 10)
# define T_NBR				(1 << 11)

# define MASK 0b111111

# define OPERATORS ";|<>"

typedef struct			s_token
{
	int					type;
	int					fd;
	char				*data;
	struct s_token		*next;
}						t_token;

typedef struct			s_lexer
{
	int					flags;
	int					count;
	struct s_token		*head;
	struct s_token		*last;
}						t_lexer;

int						valid_str(char c);
int						jump_to_next_quote(char *input, int q);
void					add_token(t_lexer *lexer, char *data);
void					tokenize(t_lexer **lexer, char *input);
void					lexer_debug(t_lexer *lexer);

#endif
