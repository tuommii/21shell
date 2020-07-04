/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/04 16:44:39 by mtuomine         ###   ########.fr       */
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

static char *check_wo_moving_cursor(char buffer[INPUT_BUFFER], int cursor)
{
	if (!buffer || !cursor)
		return (CTX_EXEC);

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


void get_completions(t_completions **comps)
{
	// t_completions *comps;
	// comps = malloc(sizeof(t_completions));
	// comps->count = 0;
	if ((*comps)->ctx == CTX_EXEC)
	{
	}
	else if ((*comps)->ctx == CTX_FLAG)
	{

	}
	else if ((*comps)->ctx == CTX_PATH)
	{

	}
	else if ((*comps)->ctx == CTX_ENV)
	{

	}
	char *example[] = {"echo", "cd", "ls", NULL};
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

static void autocomplete(t_line *line, char **suggestions)
{

	// ft_strstr()
}

void handle_autocomplete(t_line *line)
{
	t_completions *comps;
	int i;

	comps = get_context(line->input, line->pos);
	if (ft_strcmp(comps->ctx, CTX_DISCARD) == 0)
		return ;
	get_completions(&comps);
	i = 0;
	while (i < comps->count)
	{
		ft_printf("%s\n", comps->arr[i]);
		i++;
	}

	ft_printf("%d\n", comps->count);
	// autocomplete(line, arr);
	// while (*arr)
	// {
	// 	printf("%s", *arr);
	// 	arr++;
	// }
	// ft_printf("\n%s", arr[0]);
	// ft_printf("\n%s", arr[1]);
	// ft_printf("\n%s", arr[2]);

	// ft_printf("%s, %d\n", get_context(line->input, line->pos), line->pos);
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
