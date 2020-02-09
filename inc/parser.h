/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:25:25 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/09 16:33:42 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PARSER_OK 		0
# define PARSER_ERROR 	1

enum					e_cmd_type
{
	BUILTIN,
	EXEC,
	REDIR,
	PIPE
};

typedef enum e_cmd_type	t_cmd_type;

typedef struct			s_cmd
{
	t_cmd_type			type;
	char				**args;
	struct s_cmd		*next;
}						t_cmd;

int						args_count(t_token *token);
int						check_syntax(t_lexer *lexer);
t_cmd					*parser(t_lexer **lexer);

#endif
