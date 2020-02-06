/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:25:25 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/06 22:32:47 by srouhe           ###   ########.fr       */
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
	t_list				*av;
}						t_cmd;

int						check_syntax(t_lexer *lexer);
t_cmd					*parser(t_lexer **lexer);

#endif
