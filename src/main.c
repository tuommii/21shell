/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:33:42 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/26 12:42:00 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**init_env(char **env)
{
	int		i;
	int		size;
	char	**r;

	size = 0;
	while (env[size])
		size++;
	i = 0;
	if (!(r = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (env[i])
	{
		if (!(r[i] = ft_strdup(env[i])))
			return (NULL);
		i++;
	}
	r[size] = NULL;
	return (r);
}

void	create_shell(char **environ)
{
	g_sh.env = init_env(environ);
	g_sh.username = getenv("LOGNAME");
	g_sh.username_len = ft_strlen(g_sh.username);

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

void linedit_exit(t_line *line) {
	linedit_config(1);
	free_history(&line->hist);
	free(line);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **environment)
{
	char *input;
	t_line *line;
	t_lexer	*lexer;

	if (!argc || !argv || !environment)
	{
		return (1);
	}

	create_shell(environment);
	line = create_line_editor();

	while ((input = linedit(line)) != NULL)
	{
		tokenize(&lexer, input);
		if (lexer->flags & DEBUG_LEXER)
			lexer_debug(lexer);
		if ((parser(&lexer)) == PARSER_OK)
			fire_commands(lexer);
		lexer_del(&lexer);
	}
	linedit_exit(line);
}
