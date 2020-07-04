/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:33:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/04 15:55:01 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Display 21shell banner
*/

static void		display_banner(void)
{
	int		fd;
	char	*line;

	if ((fd = open(".boot", O_RDWR)) != -1)
	{
		while (get_next_line(fd, &line))
		{
			ft_putendl(line);
			free(line);
		}
		close(fd);
	}
}

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
		toggle_raw(1, 0);
		tokenize(&lexer, input);
		if (lexer->flags & DEBUG_LEXER)
			lexer_debug(lexer);
		else
			parser(&lexer) == PARSER_OK ? execute_all(lexer) : PASS;
		lexer_del(&lexer);
		toggle_raw(0, 0);
	}
	toggle_raw(1, 0);
}

int				main(int argc, char **argv, char **environment)
{
	t_line *line;

	if (!argc || !argv || !environment)
		return (1);
	linedit_setup();
	line = create_line_editor();
	create_shell(environment, line);
	display_banner();
	run_21(line);
	cleanup(line);
}
