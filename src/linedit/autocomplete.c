/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/06 20:15:27 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// make those checks, that doesnt require moving cursor
static char *check_wo_moving_cursor(char buffer[INPUT_BUFFER], int cursor)
{
	if (cursor < 0)
	{
		return (CTX_DISCARD);
	}

	if (buffer[cursor] == '$')
	{
		return (CTX_DISCARD);
	}
	else if (buffer[cursor] == '<')
	{
		return (CTX_DISCARD);
	}
	else if (buffer[cursor] == '>')
	{
		return (CTX_DISCARD);
	}
	else if (buffer[cursor] == '|')
	{
		return (CTX_DISCARD);
	}
	else if (buffer[cursor] == ';')
	{
		return (CTX_DISCARD);
	}
	else if (buffer[cursor] == '-')
	{
		return (CTX_DISCARD);
	}
	else if (buffer[cursor] == '=')
	{
		return (CTX_DISCARD);
	}


	if (cursor > ft_strlen(buffer))
	{
		return (CTX_DISCARD);
	}

	if (buffer[cursor] == ' ' && buffer[cursor - 1] == ' ')
	{
		return (CTX_DISCARD);
	}

	return (NULL);
}


// =================================================
// GET BINARIES

static int	ft_env_exists(char *name, char *given, int len_given)
{
	if (ft_strncmp(name, given, len_given) == 0 \
	&& name[len_given] && name[len_given] == '=')
		return (1);
	return (0);
}

char		*ft_getenv(char *name, char **envs)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(name);
	if (!name || ft_strequ(name, "$"))
		return (NULL);
	while (envs[i])
	{
		if (ft_env_exists(envs[i], name, len))
			return (&envs[i][len + 1]);
		i++;
	}
	return (NULL);
}


void get_binaries(char **envs)
{
	char **paths;

	paths = ft_strsplit(ft_getenv("PATH", envs), ':');
	int i = 0;
	while (paths != NULL && paths[i])
	{
		ft_printf("%s\n", paths[i]);
		i++;
	}
	if (paths != NULL)
		ft_free_arr(paths);
}
// =================================================
// END OF GET BINARIES


// returns string until to cursor, discards spaces
static char *get_current_word(char buffer[INPUT_BUFFER], int cursor)
{
	int x = cursor;
	int len = ft_strlen(buffer);

	// input is empty
	if (!x && buffer[x] == '\0')
	{
		return ft_strdup("");
	}

	// cursor is top of first char
	if (x && !ft_isspace(buffer[x]) && ft_isspace(buffer[x - 1]))
	{
		return ft_strdup(" ");
	}

	// cursor is at end of string
	if (x == len)
	{
		x--;
		while (x > 0 && !ft_isspace(buffer[x]))
			x--;
	}

	// cursor is middle of something

	// cursor is top of space
	else if (ft_isspace(buffer[x]))
	{
		x--;
		if (ft_isspace(buffer[x]))
		{
			return ft_strdup(" ");
		}
		// if (x > 0)
		// 	x--;
		while (x > 0 && !ft_isspace(buffer[x]))
		{
			x--;
		}
	}

	// cursor is top of string
	else if (!ft_isspace(buffer[x]))
	{
		while (x > 0 && !ft_isspace(buffer[x]))
			x--;
		// return ft_strdup("");
	}

	if (x || ft_isspace(buffer[x]))
		x++;
	int size = cursor - x;
	ft_printf("\nX: %d, SIZE: %d\n", x, size);
	char *res = malloc(sizeof(char) * size + 1);
	ft_strncpy(res, buffer + x, size);
	res[size] = '\0';
	return res;
}

// decide context
t_completions *get_context(char buffer[INPUT_BUFFER], int cursor)
{
	t_completions *comps;

	if (!(comps = malloc(sizeof(t_completions))))
		return (NULL);

	// if ((comps->ctx = check_wo_moving_cursor(buffer, cursor)))
	// 	return (comps);

	comps->word = get_current_word(buffer, cursor);
	ft_printf("\nCurrent word is: [%s], [%d]\n", comps->word, cursor);

	if (comps->word[0] == '\0' || (ft_strlen(comps->word) - cursor) <= 0)
	{
		comps->ctx = ft_strdup(CTX_EXEC);
	}

	else if (comps->word[0] == '$')
	{
		comps->ctx = ft_strdup(CTX_ENV);
	}

	else if (comps->word[0] == '-')
	{
		comps->ctx = ft_strdup(CTX_FLAG);
	}

	// else if (comps->word[0] == '/' || comps->word[0] == '.' || comps->word[0] == ' ')
	else
	{
		comps->ctx = ft_strdup(CTX_PATH);
	}
	return (comps);
}

// get all available suggestions for right context
void suggestions(t_line *line, t_completions **comps)
{
	// if ((*comps)->ctx == CTX_EXEC)
	// {
	// 	char *example[] = {"echo", "echo-example-2", "ls-example", NULL};
	// 	char **pp = example;
	// 	(*comps)->suggestions = malloc(sizeof(char *) * 4);
	// 	int i = 0;
	// 	while (*pp)
	// 	{
	// 		(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
	// 		ft_strcpy((*comps)->suggestions[i], *pp);
	// 		i++;
	// 		pp++;
	// 	}
	// 	(*comps)->count = i;
	// 	return ;
	// }
	// else if ((*comps)->ctx == CTX_FLAG)
	// {
	// 	char *example[] = {"-all-flag", "-help-flag", "-version-flag", NULL};
	// 	char **pp = example;

	// 	(*comps)->suggestions = malloc(sizeof(char *) * 4);
	// 	int i = 0;
	// 	while (*pp)
	// 	{
	// 		(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
	// 		ft_strcpy((*comps)->suggestions[i], *pp);
	// 		i++;
	// 		pp++;
	// 	}
	// 	(*comps)->count = i;
	// 	return ;
	// }
	// else if ((*comps)->ctx == CTX_PATH)
	// {
	// 	char *example[] = {"filename-example", "dir-example", "Makefile-example", NULL};
	// 	char **pp = example;
	// 	(*comps)->suggestions = malloc(sizeof(char *) * 4);
	// 	int i = 0;
	// 	while (*pp)
	// 	{
	// 		(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
	// 		ft_strcpy((*comps)->suggestions[i], *pp);
	// 		i++;
	// 		pp++;
	// 	}
	// 	(*comps)->count = i;
	// 	return ;
	// }
	// else if ((*comps)->ctx == CTX_ENV)
	// {
	// 	char **cpy = line->envs;
	// 	int i = 0;
	// 	while (*cpy)
	// 	{
	// 		//ft_printf("%d %s\n",(*comps)->count,  *cpy);
	// 		//(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*cpy) + 1);
	// 		//ft_strcpy((*comps)->suggestions[i], *cpy);
	// 		cpy++;
	// 		i++;
	// 	}
	// 	char **cpy2 = line->envs;
	// 	(*comps)->count = i;
	// 	ft_printf("\n%d\n", i);
	// 	(*comps)->suggestions = malloc(sizeof(char *) * i + 1);

	// 	i = 0;
	// 	while (i < (*comps)->count)
	// 	{
	// 		int len = ft_strlen(line->envs[i]) + 1;
	// 		(*comps)->suggestions[i] = malloc(sizeof(char) * len);
	// 		ft_strcpy((*comps)->suggestions[i], line->envs[i]);
	// 		i++;
	// 	}
	// 	//(*comps)->suggestions[i] = NULL;
	// 	return ;
	// }
	// Example
	char *example[] = {"echo", "echo-example-3", "echo-example", NULL};
	char **pp = example;
	int i = 0;
	(*comps)->suggestions = malloc(sizeof(char *) * 4);
	while (*pp)
	{
		(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*pp) + 1);
		ft_strcpy((*comps)->suggestions[i], *pp);
		i++;
		pp++;
	}
	(*comps)->count = i;
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
	if (!comps->word || !comps->word[0])
		return ;
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
	free(comps->word);
	free(comps->suggestions);
	free(comps);
}


// complete word based on current word
static void autocomplete(t_line *line, t_completions *comps)
{
	suggestions(line, &comps);
	char **cpy = comps->suggestions;

	// ft_printf("\nCopied suggestions without segfault\n");

	if (!(comps->word = get_current_word(line->input, line->pos)))
		return ;

	if (!comps->word[0])
		return ;

	ft_printf("\nSTARTING FILTER\n");
	filter(comps);
	ft_printf("\nFILTERED\n");


	// ft_printf("\nFiltered\n");
	if (!comps->matches_count)
	{
		// clean(comps);
		return ;
	}
	sort_by_length(comps);
	delete_word(line, comps->word);
	// Shortest is first
	insert_word(line, comps->matches[0]);
	// clean(comps);
}

// called when tab is pressed
void handle_autocomplete(t_line *line)
{
	t_completions *comps;
	int i;

	if (!(comps = get_context(line->input, line->pos)))
		return ;
	ft_printf("\n%s\n", comps->ctx);
	if (ft_strcmp(comps->ctx, CTX_DISCARD) == 0)
	{
		free(comps->word);
		free(comps);
		return ;
	}
	ft_printf("COMPARED CTX: %s", comps->ctx);
	ft_printf("COMPARED WORD: %s", comps->word);
	autocomplete(line, comps);
	redraw_input(line);
}
