/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:33:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/04/03 10:43:52 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Create Abstract syntax tree from lexer and execute
*/

static void		execute_all(t_lexer *lexer)
{
	t_ast	*ast;

	if ((ast = ast_create(&lexer->head)) != NULL)
	{
		ast && lexer->flags & DEBUG_AST ? ast_debug(ast, 0) : PASS;
		ast->flags = lexer->flags;
		execution_init(ast);
		ast_del(&ast);
	}
}

static void		run_21(t_line *line)
{
	char *input;
	t_lexer	*lexer;

	while ((input = linedit(line)) != NULL)
	{
		linedit_config(1);
		tokenize(&lexer, input);
		lexer->flags & DEBUG_LEXER ? lexer_debug(lexer) : PASS;
		parser(&lexer) == PARSER_OK ? execute_all(lexer) : PASS;
		lexer_del(&lexer);
		linedit_config(0);
	}
}

int				main(int argc, char **argv, char **environment)
{
	t_line *line;

	if (!argc || !argv || !environment)
	{
		return (1);
	}
	// Display cool banner!
	create_shell(environment);
	linedit_setup();
	line = create_line_editor();
	g_sh.line = line; // Unecessary?
	run_21(line);
	cleanup(line);
}