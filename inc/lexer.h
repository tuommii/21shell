/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:56:02 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/31 12:48:31 by srouhe           ###   ########.fr       */
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
# define T_IO			(1 << 8)
# define T_STR			(1 << 9)
# define DEBUG_LEXER	(1 << 10)
# define DEBUG_AST		(1 << 11)

# define MASK_STR		0b1000000000
# define MASK_OP 		0b11
# define MASK_REDIR 	0b111100
# define MASK_CTRL		0b111111

# define OPERATORS 		";|<>"
# define OPERATOR_ARR 	"|", ";", ">>", "<<", "<&", "<>", ">&", ">|", "<<-", ">", "<" 
# define OP_SLOTS		11
# define OP_LEN			3
# define STRING			9

# define OPT_LEXER		"--lexer"
# define OPT_AST		"--ast"

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

int						str_valid_char(char c);
int						next_quote(char *input, int q);
int						tokenize_operator(t_lexer *lexer, char *input);
int						tokenize_string(t_lexer *lexer, char *input);
void					add_token(t_lexer *lexer, char *data, int flag);
void					tokenize(t_lexer **lexer, char *input);
void					lexer_del(t_lexer **lexer);

#endif
