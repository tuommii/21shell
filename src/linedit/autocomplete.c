/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/04 22:53:35 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// TODO: Enum?
# define CTX_EXEC "EXEC"
# define CTX_FLAG "FLAG"
# define CTX_PATH "PATH"
# define CTX_ENV "ENV"
# define CTX_DISCARD "DISCARD"



// TODO: Reset context with  "|;" and what else?
# define CTX_DISCARD_STR "|;<>-$"
# define MAX_MATCHES 10

static char *check_wo_moving_cursor(char buffer[INPUT_BUFFER], int cursor)
{
	if (!buffer || !cursor)
	{
		return (CTX_EXEC);
	}

	if (cursor > ft_strlen(buffer))
	{
		ft_printf("CURSOR > LEN\n");
		return (CTX_DISCARD);
	}

	if (buffer[cursor] == ' ' && buffer[cursor - 1] == ' ')
	{
		ft_printf("SPACES\n");
		return (CTX_DISCARD);
	}

	if (ft_strchr(CTX_DISCARD_STR, buffer[cursor]) && buffer[cursor] != '\0')
	{
		ft_printf("TOP OF CHAR\n");
		return (CTX_DISCARD);
	}

	return (NULL);
}

t_completions *get_context(char buffer[INPUT_BUFFER], int cursor)
{
	t_completions *comps;

	if (!(comps = malloc(sizeof(t_completions))))
		return (NULL);

	if ((comps->ctx = check_wo_moving_cursor(buffer, cursor)))
		return (comps);

	// Discard extra spaces
	while (buffer[cursor] == ' ')
		cursor--;

	while (cursor && buffer[cursor] != ' ')
		cursor--;
	if (!cursor)
		comps->ctx = CTX_EXEC;
	else if (buffer[cursor - 1] == '|' || buffer[cursor - 1] == ';')
		comps->ctx = CTX_EXEC;
	else if (buffer[cursor + 1] == '|' || buffer[cursor + 1] == ';')
		comps->ctx = CTX_EXEC;
	else if (buffer[cursor + 1] == '-')
		comps->ctx = CTX_FLAG;
	else if (buffer[cursor + 1] == '/' || buffer[cursor + 1] == '.')
		comps->ctx = CTX_PATH;
	else if (buffer[cursor + 1] == '$')
		comps->ctx = CTX_ENV;
	else
		comps->ctx = CTX_PATH;
	return (comps);
}


void suggestions(t_completions **comps)
{
	if ((*comps)->ctx == CTX_EXEC)
	{
		char *example[] = {"echo-example", "echo-examppelepl2", "ls-example", NULL};
		char **pp = example;
		(*comps)->arr = malloc(sizeof(char *) * 4);
		int i = 0;
		while (*pp)
		{
			(*comps)->arr[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
			ft_strcpy((*comps)->arr[i], *pp);
			i++;
			pp++;
		}
		(*comps)->count = i;
	}
	else if ((*comps)->ctx == CTX_FLAG)
	{
		char *example[] = {"-all-flag-example", "-version", "-help", NULL};
		char **pp = example;
		(*comps)->arr = malloc(sizeof(char *) * 4);
		int i = 0;
		while (*pp)
		{
			(*comps)->arr[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
			ft_strcpy((*comps)->arr[i], *pp);
			i++;
			pp++;
		}
		(*comps)->count = i;
	}
	else if ((*comps)->ctx == CTX_PATH)
	{
		char *example[] = {"/testi1", "/home", "/filename-example", NULL};
		char **pp = example;
		(*comps)->arr = malloc(sizeof(char *) * 4);
		int i = 0;
		while (*pp)
		{
			(*comps)->arr[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
			ft_strcpy((*comps)->arr[i], *pp);
			i++;
			pp++;
		}
		(*comps)->count = i;
	}
	else if ((*comps)->ctx == CTX_ENV)
	{
		char *example[] = {"$HOME-EXAMPLE", "$USER", "$CWD", NULL};
		char **pp = example;
		(*comps)->arr = malloc(sizeof(char *) * 4);
		int i = 0;
		while (*pp)
		{
			(*comps)->arr[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
			ft_strcpy((*comps)->arr[i], *pp);
			i++;
			pp++;
		}
		(*comps)->count = i;
	}
}

// sets comps->word to string thats under or behind cursor
static void current_word(t_line *line, t_completions *comps)
{
	int pos;

	if (!line->pos)
		return (NULL);
	pos = line->pos - 1;
	while (pos && line->input[pos] != ' ')
		pos--;
	if (pos)
		pos++;
	int len = line->pos - pos;
	ft_bzero(comps->word, INPUT_BUFFER);
	ft_strncpy(comps->word, line->input + pos, len);
	comps->word[len] = '\0';
}

static void add_char(t_line *line, char c)
{
	if (line->len >= INPUT_BUFFER)
		return ;
	if (line->pos == line->len)
	{
		line->input[line->pos] = c;
	}
	else
	{
		ft_insert(line->input, line->pos + 1, c);
	}
	line->len++;
	line->pos++;
}

static void delete_word(t_line *line, char *word)
{
	int len = ft_strlen(word);
	while (len)
	{
		line->input[line->pos - 1] = '\0';
		line->pos--;
		line->len--;
		len--;
	}
}

static void insert_word(t_line *line, char *word)
{
	while (*word)
	{
		add_char(line, *word);
		word++;
	}
}

static void autocomplete(t_line *line, t_completions *comps)
{
	char *matches[MAX_MATCHES];

	int j = 0;
	while (j < MAX_MATCHES)
	{
		matches[j] = malloc(sizeof(char) * 128);
		j++;
	}
	j = 0;


	int i;
	i = 0;
	while (i < comps->count)
	{
		char *cpy;
		if ((cpy = ft_strstr(comps->arr[i], comps->word)))
		{
			ft_strcpy(matches[j], comps->arr[i]);
			j++;
			// delete_word(line, comps->word);
			// insert_word(line, cpy);
			// break ;
		}
		i++;
	}

	j = 0;
	// ft_printf("ci:%d, j:%d, %s\n", ci, j, matches[ci]);
	delete_word(line, comps->word);
	insert_word(line, matches[j]);
}

void handle_autocomplete(t_line *line)
{
	t_completions *comps;
	int i;

	comps = get_context(line->input, line->pos);
	if (ft_strcmp(comps->ctx, CTX_DISCARD) == 0)
		return ;

	suggestions(&comps);
	current_word(line, comps);
	autocomplete(line, comps);

	redraw_input(line);
}


// gcc autocomplete.c -I ../inc -I ../libft/
// int main() {

// 	char test[INPUT_BUFFER] = "ls  -all $HOME   /home ; echo \"Miikka\"";
// 	char test2[INPUT_BUFFER] = "echo  $HOME";

// 	int i = 0;
// 	while (i < strlen(test))
// 	{
// 		printf("cursor: %c, %s\n", test[i], get_context(test, i));
// 		i++;
// 	}
// 	return (0);
// }
