/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 00:13:39 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// returns string until to cursor, discards spaces
static char *get_word_at(char buffer[INPUT_BUFFER], int cursor)
{
	int x = cursor;
	int len = ft_strlen(buffer);
	char *res;

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
		if (x)
			x--;
		if (ft_isspace(buffer[x]))
		{
			return ft_strdup(" ");
		}
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
	}

	if (x || ft_isspace(buffer[x]))
		x++;
	int size = cursor - x;
	res = malloc(sizeof(char) * size + 1);
	ft_strncpy(res, buffer + x, size);
	res[size] = '\0';
	return res;
}

// decide context
char *get_context(char buffer[INPUT_BUFFER], int cursor)
{
	char *word;
	char *ctx;

	if (!(word = get_word_at(buffer, cursor)))
	{
		free(word);
		return (NULL);
	}

	if (word[0] == '\0' || (ft_strlen(word) - cursor) <= 0)
	{
		ctx = ft_strdup(CTX_EXEC);
	}

	else if (word[0] == '$')
	{
		ctx = ft_strdup(CTX_ENV);
	}

	else if (word[0] == '-')
	{
		ctx = ft_strdup(CTX_FLAG);
	}

	else if (!cursor && buffer[cursor] == ' ')
	{
		ctx = ft_strdup(CTX_EXEC);
	}

	// TODO: recursive with ' '
	// else if (word[0] == '/' || word[0] == '.' || word[0] == ' ')
	else
	{
		ctx = ft_strdup(CTX_PATH);
	}
	free(word);
	return (ctx);
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
	if (!comps->word)
		return ;

	char *cpy = comps->word;
	if (cpy[0] == '$' && cpy[1])
	{
		cpy++;
	}

	int len = ft_strlen(cpy);
	int i = 0;
	int count = 0;

	while (i < comps->count)
	{
		if (ft_strncmp(comps->suggestions[i], cpy, len) == 0)
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

	while (i < comps->matches_count - 1 && i < MAX_MATCHES - 1)
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

static void clean_suggestions(t_completions *comps)
{
	int i = 0;
	while (i < comps->count)
	{
		free(comps->suggestions[i]);
		comps->suggestions[i] = NULL;
		i++;
	}
	free(comps->suggestions);
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
	clean_suggestions(comps);
	free(comps->word);
	free(comps->ctx);
	free(comps);
}


// get all available suggestions for right context
void set_suggestions(t_line *line, t_completions **comps)
{
	if (suggestions_env(line, comps))
		return ;
	// Example
	char *example[] = {"echo", "echo-example-3", "$HOME", NULL};
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


// complete word based on current word
static void autocomplete(t_line *line, t_completions *comps)
{
	set_suggestions(line, &comps);

	if (!(comps->word = get_word_at(line->input, line->pos)))
	{
		clean_suggestions(comps);
		free(comps->ctx);
		free(comps);
		return ;
	}

	// after this, matches and matches_count is available
	filter(comps);

	if (!comps->matches_count)
	{
		clean_suggestions(comps);
		free(comps->ctx);
		free(comps->word);
		free(comps);
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

	comps = NULL;
	if (!(comps = malloc(sizeof(t_completions))))
		return ;

	comps->len = 0;
	comps->word = NULL;
	comps->matches_count = 0;
	comps->ctx = NULL;
	comps->suggestions = NULL;
	if (!(comps->ctx = get_context(line->input, line->pos)))
		return ;

	ft_printf("\n%s\n", comps->ctx);

	if (ft_strcmp(comps->ctx, CTX_DISCARD) == 0)
	{
		free(comps->ctx);
		free(comps);
		return ;
	}
	autocomplete(line, comps);
	redraw_input(line);
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

int suggestions_env(t_line *line, t_completions **comps)
{
	if (ft_strcmp((*comps)->ctx, CTX_ENV) == 0)
	{
		char **cpy = line->envs;
		int i = 0;
		while (*cpy)
		{
			//ft_printf("%d %s\n",(*comps)->count,  *cpy);
			//(*comps)->suggestions[i] = malloc(sizeof(char) * ft_strlen(*cpy) + 1);
			//ft_strcpy((*comps)->suggestions[i], *cpy);
			cpy++;
			i++;
		}
		char **cpy2 = line->envs;
		(*comps)->count = i;
		ft_printf("\n%d\n", i);
		(*comps)->suggestions = malloc(sizeof(char *) * i + 1);

		i = 0;
		while (i < (*comps)->count)
		{
			int len = ft_strlen(line->envs[i]) + 1;
			(*comps)->suggestions[i] = malloc(sizeof(char) * len);
			ft_strcpy((*comps)->suggestions[i], line->envs[i]);
			i++;
		}
		//(*comps)->suggestions[i] = NULL;
		return (1);
	}
	return (0);
}
