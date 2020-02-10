/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:25:25 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/10 17:16:54 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PARSER_OK 		0
# define PARSER_ERROR 	1
# define AST_COUNT		10

enum					e_cmd_type
{
	BUILTIN,
	EXEC,
	REDIR,
	PIPE
};

typedef enum e_cmd_type	t_cmd_type;

typedef struct			s_ast
{
	t_token				*token;
	struct s_ast		*parent;
	struct s_ast		*left;
	struct s_ast		*right;
	int					type;
	int					operator;
}						t_ast;

int						args_count(t_token *token);
int						check_syntax(t_lexer *lexer);
int						parser(t_lexer **lexer);
t_ast					*create_ast(t_token **token);

#endif
