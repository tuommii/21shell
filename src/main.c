/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/13 16:03:26 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "exec.h"

// free mem also
void	exit_error(int errno)
{
	reset_shell();
	errno == 2 ? ft_putendl("malloc error.") : NULL;
	exit(errno);
}

void cleanup(void)
{
	// TODO: Free fields aldo
	ft_freestrarr(g_sh.env);
	config_terminal(1);
	return exit(EXIT_SUCCESS);
}

// After ENTER pressed, reset variables
void reset_shell(void)
{
	if (g_sh.key == ENTER)
	{
		ft_printf("\n");
	}
	g_sh.i = 0;
	g_sh.x = g_sh.prompt_len;
	g_sh.y++;
	if (g_sh.y > g_sh.rows)
		g_sh.y = g_sh.rows;
	g_sh.len = 0;
	ft_bzero(g_sh.input, INPUT_BUFFER);
}


static int read_input(void)
{
	while ((g_sh.key = keypress()) != ENTER)
	{
		watch_kill();
		which_key();
		//print_debug(sh);
		print_input();
	}
	// TODO: Prevent adding same than last
	end_of_input();
	g_sh.hist_i = 0;
	if (*g_sh.input)
	{
		g_sh.hist_count += hist_append(&g_sh.hist, g_sh.input);
	}
	return (ENTER);
}


static void	fire_commands(t_lexer *lexer)
{
	t_ast	*ast;

	ast = ast_create(&lexer->head);
	if (ast && lexer->flags & DEBUG_AST)
	{
		tputs(tgetstr("cl", NULL), 1, print_char);
		ast_debug(ast, 0);
	}
	execution_init(ast);
	ast_del(&ast);
}

static void run_shell(void)
{
	int		r;
	t_lexer	*lexer;
	
	while (1)
	{
		listen_signals();
		//print_debug();
		print_prompt();
		if ((g_sh.key = read_input()) == ESC)
			return ;
		tokenize(&lexer, g_sh.input);
		// ft_printf("    first token: [%s] last token: [%s]", lexer->head->data, lexer->last->data);
		if (lexer->flags & DEBUG_LEXER)
			lexer_debug(lexer);
		if ((r = parser(&lexer)) == PARSER_OK)
			fire_commands(lexer);
		// parser_debug(ast);
		lexer_del(&lexer);
		// hist_print(g_sh.hist);
		// if (g_sh.hist && g_sh.hist->prev)
		// 	ft_printf("INDEX: %d, LAST: %s", g_sh.hist->prev->i, g_sh.hist->prev->str);
		reset_shell();
	}
}

int	main(int argc, char **argv, char **environ)
{
	setup(argc, argv, environ);
	create_shell(environ);
	run_shell();
	cleanup();
}
