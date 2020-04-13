/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:33:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/04/13 19:20:13 by srouhe           ###   ########.fr       */
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
		if (ast && lexer->flags & DEBUG_AST)
			ast_debug(ast, 0);
		else
		{
			ast->flags = lexer->flags;
			g_sh.status = execution_init(ast);
			// ft_printf("Execution status: [%d]\n", g_sh.status);
		}
		ast_del(&ast);
	}
}

/*
** Read from stdin, tokenize input and send to parser
*/

static void		run_21(t_line *line)
{
	char	*input;
	t_lexer	*lexer;

	listen_signals();
	while ((input = linedit(line)) != NULL)
	{
		tokenize(&lexer, input);
		if (lexer->flags & DEBUG_LEXER)
			lexer_debug(lexer);
		else
			parser(&lexer) == PARSER_OK ? execute_all(lexer) : PASS;
		lexer_del(&lexer);
	}
	linedit_config(1);
}

int				main(int argc, char **argv, char **environment)
{
	t_line *line;

	if (!argc || !argv || !environment)
	{
		return (1);
	}
	// Display cool banner!
	linedit_setup();
	line = create_line_editor();
	create_shell(environment, line);
	run_21(line);
	cleanup(line);
}
