/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:33:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/04/02 10:49:43 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Create Abstract syntax tree from lexer and execute
*/

static void		execute_all(t_lexer *lexer)
{
	t_ast	*ast;

	ast = ast_create(&lexer->head);
	if (ast && lexer->flags & DEBUG_AST)
		ast_debug(ast, 0);
	execution_init(ast);
	ast_del(&ast);
}

static void		run_21(t_line *line)
{
	char *input;
	t_lexer	*lexer;

	while ((input = linedit(line)) != NULL)
	{
		tokenize(&lexer, input);
		if (lexer->flags & DEBUG_LEXER)
			lexer_debug(lexer);
		if ((parser(&lexer)) == PARSER_OK)
			execute_all(lexer);
		lexer_del(&lexer);
	}
}

int				main(int argc, char **argv, char **environment)
{
	t_line *line;

	if (!argc || !argv || !environment)
	{
		return (1);
	}
	create_shell(environment);
	linedit_setup();
	line = create_line_editor();
	g_sh.line = line;
	run_21(line);
	cleanup(line);
}
