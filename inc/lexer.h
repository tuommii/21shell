/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:56:02 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/05 15:49:43 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define T_PIPE			(1 << 0)
# define T_SCOL			(1 << 1)
# define T_DRARR		(1 << 2)
# define T_DLARR		(1 << 3)
# define T_SRARR		(1 << 4)
# define T_SLARR		(1 << 5)
# define T_STR			(1 << 9)
# define MASK 			0b111111

# define UNDEFINED		0
# define OP				1
# define STRING			9

# define OPERATORS 		";|<>"
# define OPERATOR_ARR 	"|", ";", ">>", "<<", ">", "<"
# define OP_SLOTS		6
# define OP_LEN			3

typedef struct			s_token
{
	int					type;
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
int						next_quote(char *input, int q);
void					add_token(t_lexer *lexer, char *data, int flag);
void					tokenize(t_lexer **lexer, char *input);
void					lexer_debug(t_lexer *lexer);

#endif
