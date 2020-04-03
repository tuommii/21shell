/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:25:25 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/03 10:42:55 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PARSER_OK 		0
# define PARSER_ERROR 	1
# define AST_COUNT		10
# define D_QUOTE		34
# define S_QUOTE		39

typedef enum e_cmd_type	t_cmd_type;

typedef struct			s_ast
{
	t_token				*token;
	t_token				*cmd_end;
	struct s_ast		*parent;
	struct s_ast		*left;
	struct s_ast		*right;
	int					flags;
	int					type;
	int					nbr_token;
}						t_ast;

int						check_syntax(t_lexer *lexer);
int						parser(t_lexer **lexer);
int						next_operator(t_token *token, int type);
void					ast_del(t_ast **ast);
t_ast					*ast_create(t_token **token);
t_ast					*new_leaf(t_token **token);
t_ast					*new_node(t_ast *left, t_ast *parent, t_ast *right);

#endif
