/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/05 23:09:27 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// make those checks, that doesnt require moving cursor
static char *check_wo_moving_cursor(char buffer[INPUT_BUFFER], int cursor)
{

	if (ft_strchr(CTX_DISCARD_STR, buffer[cursor]) && buffer[cursor] != '\0')
	{
		// ft_printf("TOP OF CHAR\n");
		return (CTX_DISCARD);
	}

	if (!buffer || !cursor)
	{
		return (CTX_EXEC);
	}

	if (cursor > ft_strlen(buffer))
	{
		// ft_printf("CURSOR > LEN\n");
		return (CTX_DISCARD);
	}

	if (buffer[cursor] == ' ' && buffer[cursor - 1] == ' ')
	{
		// ft_printf("SPACES\n");
		return (CTX_DISCARD);
	}

	return (NULL);
}

// decide context
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
	// if (!cursor)
	if (buffer[cursor] == '$' || buffer[cursor + 1] == '$' || buffer[cursor - 1] == '$')
		comps->ctx = CTX_ENV;
	else if (!cursor)
		comps->ctx = CTX_EXEC;
	else if (buffer[cursor - 1] == '|' || buffer[cursor - 1] == ';')
		comps->ctx = CTX_EXEC;
	else if (buffer[cursor + 1] == '|' || buffer[cursor + 1] == ';')
		comps->ctx = CTX_EXEC;
	else if (buffer[cursor + 1] == '-')
		comps->ctx = CTX_FLAG;
	else if (buffer[cursor + 1] == '/' || buffer[cursor + 1] == '.')
		comps->ctx = CTX_PATH;
	else if (buffer[cursor - 1] == '$')
		comps->ctx = CTX_ENV;
	else
		comps->ctx = CTX_PATH;
	return (comps);
}

// get all available suggestions for right context
void suggestions(t_completions **comps)
{
	if ((*comps)->ctx == CTX_EXEC)
	{
		char *example[] = {"echo", "echo-example-2", "ls-example", NULL};
		char **pp = example;
		(*comps)->suggestions = malloc(sizeof(char *) * 4);
		int i = 0;
		while (*pp)
		{
			(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
			ft_strcpy((*comps)->suggestions[i], *pp);
			i++;
			pp++;
		}
		(*comps)->count = i;
		return ;
	}
	else if ((*comps)->ctx == CTX_FLAG)
	{
		char *example[] = {"-all-flag", "-help-flag", "-version-flag", NULL};
		char **pp = example;
		(*comps)->suggestions = malloc(sizeof(char *) * 4);
		int i = 0;
		while (*pp)
		{
			(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
			ft_strcpy((*comps)->suggestions[i], *pp);
			i++;
			pp++;
		}
		(*comps)->count = i;
		return ;
	}
	else if ((*comps)->ctx == CTX_PATH)
	{
		char *example[] = {"filename-example", "dir-example", "Makefile-example", NULL};
		char **pp = example;
		(*comps)->suggestions = malloc(sizeof(char *) * 4);
		int i = 0;
		while (*pp)
		{
			(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
			ft_strcpy((*comps)->suggestions[i], *pp);
			i++;
			pp++;
		}
		(*comps)->count = i;
		return ;
	}
	else if ((*comps)->ctx == CTX_ENV)
	{
		char *example[] = {"$HOME-EXAMPLE", "$USER-EXAMPLE", "$CWD", NULL};
		char **pp = example;
		(*comps)->suggestions = malloc(sizeof(char *) * 4);
		int i = 0;
		while (*pp)
		{
			(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
			ft_strcpy((*comps)->suggestions[i], *pp);
			i++;
			pp++;
		}
		(*comps)->count = i;
		return ;
	}
	// Example
	// char *example[] = {"echo", "echo-example-3", "echo-example", NULL};
	// char **pp = example;
	// (*comps)->suggestions = malloc(sizeof(char *) * 4);
	// int i = 0;
	// while (*pp)
	// {
	// 	(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
	// 	ft_strcpy((*comps)->suggestions[i], *pp);
	// 	i++;
	// 	pp++;
	// }
	// (*comps)->count = i;
}

// sets comps->word to current word (string thats under or behind cursor)
static void current_word(t_line *line, t_completions *comps)
{
	int pos;

	if (!line->pos)
	{
		comps->word[0] = '\0';
		return (NULL);
	}
	pos = line->pos - 1;
	while (pos && line->input[pos] != ' ')
		pos--;
	if (pos)
		pos++;
	while (line->input[pos] == '\"')
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

	// If cursor is in the middle of word
	while (line->input[line->pos] != ' ')
	{
		if (line->input[line->pos] == '\0')
			break;
		line->pos++;
		len++;
	}

	while (len)
	{
		ft_insert(line->input, line->pos, 0);
		line->pos--;
		line->len--;
		len--;
	}
}

static void insert_word(t_line *line, char *word)
{
	int i = 0;

	while (*word)
	{
		apped_or_insert(line, *word);
		word++;
	}
}

// copy suitable suggestions only
static void filter(t_completions *comps)
{
	int len = ft_strlen(comps->word);
	int i = 0;
	int count = 0;

	while (i < comps->count)
	{
		if (ft_strncmp(comps->suggestions[i], comps->word, len) == 0)
		{
			if (ft_strlen(comps->suggestions[i]) > len)
			{
				comps->matches[count] = malloc(sizeof(char) * ft_strlen(comps->suggestions[i]) + 1);
				ft_strcpy(comps->matches[count], comps->suggestions[i]);
				count++;
			}
		}
		i++;
	}
	comps->matches_count = count;
}

// sort comp->matches by length so we get shortest first
static void sort_by_length(t_completions *comps)
{
	int i = 0;
	char *temp;

	while (i < comps->matches_count - 1)
	{
		int a = ft_strlen(comps->matches[i]);
		int b = ft_strlen(comps->matches[i + 1]);
		if (a > b)
		{
			temp = comps->matches[i];
			comps->matches[i] = comps->matches[i + 1];
			comps->matches[i + 1] = temp;
			i = 0;
		}
		else
		{
			i++;
		}
	}
}

static void clean(t_completions *comps)
{
	int i = 0;
	while (i < comps->matches_count)
	{
		free(comps->matches[i]);
		comps->matches[i] = NULL;
		i++;
	}

	i = 0;
	while (i < comps->count)
	{
		free(comps->suggestions[i]);
		comps->suggestions[i] = NULL;
		i++;
	}
	free(comps->suggestions);
	free(comps);
}


// complete word based on current word
static void autocomplete(t_line *line, t_completions *comps)
{
	suggestions(&comps);
	current_word(line, comps);
	filter(comps);
	if (!comps->matches_count)
	{
		clean(comps);
		return ;
	}
	sort_by_length(comps);
	delete_word(line, comps->word);
	// Shortest is first
	insert_word(line, comps->matches[0]);
	clean(comps);
}

// called when tab is pressed
void handle_autocomplete(t_line *line)
{
	t_completions *comps;
	int i;

	if (!(comps = get_context(line->input, line->pos)))
		return ;
	if (ft_strcmp(comps->ctx, CTX_DISCARD) == 0)
	{
		free(comps);
		return ;
	}
	autocomplete(line, comps);
	redraw_input(line);
}
