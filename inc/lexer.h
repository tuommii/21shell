/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:56:02 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/16 16:34:26 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** Token flags
*/

# define T_PIPE			(1 << 0)
# define T_SCOL			(1 << 1)
# define T_DRARR		(1 << 2)
# define T_DLARR		(1 << 3)
# define T_LESS_AND		(1 << 4)
# define T_BOTH			(1 << 5)
# define T_GREAT_AND	(1 << 6)
# define T_ARRPIPE		(1 << 7)
# define T_SRARR		(1 << 8)
# define T_SLARR		(1 << 9)
# define T_STR			(1 << 10)
# define T_SQUOT		(1 << 11)
# define T_DQUOT		(1 << 12)
# define IO_NUM			(1 << 13)
# define T_FILE			(1 << 14)
# define T_DASH			(1 << 15)
# define T_HEREDOC		(1 << 16)
# define DEBUG_LEXER	(1 << 17)
# define DEBUG_AST		(1 << 18)

/*
** Token flag masks
*/

# define MASK_STR		0b10000000000
# define MASK_OP 		0b11
# define MASK_REDIR 	0b1111111100
# define MASK_CTRL		0b1111111111
# define MASK_CMD		0b101110000000000
# define MASK_ECHO		0b1110000000000

/*
** Definitions for tokenizing
*/

# define OPERATORS 		";|<>&"
# define OPERATOR_ARR 	"|", ";", ">>", "<<", "<&", "<>", ">&", ">|", ">", "<" 
# define OP_SLOTS		10
# define OP_LEN			3

/*
** Utils for adding correct flags to tokens
*/

# define STRING			10
# define F_SQUOTE		11
# define F_DQUOTE		12
# define IO_NUMBER		13
# define FILENAME		14
# define DASH			15
# define HEREDOC		16

# define OPT_LEXER		"--lexer"
# define OPT_AST		"--ast"

typedef struct			s_token
{
	int					type;
	int					fd;
	char				*data;
	char				*heredoc;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct			s_lexer
{
	int					flags;
	int					count;
	struct s_token		*head;
	struct s_token		*last;
}						t_lexer;

int						is_valid_char(char c);
int						next_quote(char *input, int q);
int						str_isnumeric(char *str);
int						tokenize_operator(t_lexer *lexer, char *input);
int						tokenize_string(t_lexer *lexer, char *input);
void					add_token(t_lexer *lexer, char *data, int flag);
void					tokenize(t_lexer **lexer, char *input);
void					lexer_del(t_lexer **lexer);

#endif
