/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/10 19:06:06 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// free mem also
void	exit_error(t_shell *sh, int errno)
{
	reset_shell(sh);
	errno == 2 ? ft_putendl("malloc error.") : NULL;
	exit(errno);
}

void cleanup(t_shell *sh)
{
	// TODO: Free fields aldo
	free(sh);
	config_terminal(1);
	return exit(EXIT_SUCCESS);
}

// After ENTER pressed, reset variables
void reset_shell(t_shell *sh)
{
	if (sh->key == ENTER)
	{
		ft_printf("\n");
	}
	sh->i = 0;
	sh->x = sh->prompt_len;
	sh->y++;
	if (sh->y > sh->rows)
		sh->y = sh->rows;
	sh->len = 0;
	ft_bzero(sh->input, INPUT_BUFFER);
}


static int read_input(t_shell *sh)
{
	while ((sh->key = keypress()) != ENTER)
	{
		watch_kill();
		which_key(sh);
		//print_debug(sh);
		print_input(sh);
	}
	// TODO: Prevent adding same than last
	end_of_input(sh);
	sh->hist_i = 0;
	if (*sh->input)
	{
		sh->hist_count += hist_append(&sh->hist, sh->input);
	}
	return (ENTER);
}


static void	fire_commands(t_lexer *lexer)
{
	t_ast	*ast;

	ast = create_ast(&lexer->head);
	if (ast && lexer->flags & DEBUG_AST)
	{
		tputs(tgetstr("cl", NULL), 1, print_char);
		ast_debug(ast, 0);
	}
	execute(ast);
	// free abstract syntax tree
}

static void run_shell(t_shell *sh)
{
	int		r;
	t_lexer	*lexer;
	
	while (1)
	{
		listen_signals();
		//print_debug(sh);
		print_prompt(sh);
		if ((sh->key = read_input(sh)) == ESC)
			return ;
		tokenize(&lexer, sh->input);
		// ft_printf("    first token: [%s] last token: [%s]", lexer->head->data, lexer->last->data);
		if (lexer->flags & DEBUG_LEXER)
			lexer_debug(lexer);
		if ((r = parser(&lexer)) == PARSER_OK)
			fire_commands(lexer);
		// parser_debug(ast);
		// exec_cmd(cmd_lst);
		// hist_print(sh->hist);
		// if (sh->hist && sh->hist->prev)
		// 	ft_printf("INDEX: %d, LAST: %s", sh->hist->prev->i, sh->hist->prev->str);
		// free parser and lexer structs
		reset_shell(sh);
	}
}

int	main(int argc, char **argv, char **environment)
{
	t_shell *sh;
	setup(argc, argv, environment);
	sh = create_shell();
	run_shell(sh);
	cleanup(sh);
}
