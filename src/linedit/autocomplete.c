/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/04 15:37:33 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

// TODO: Enum?
# define CTX_BUILTIN "BUILTIN"
# define CTX_BINARY "BINARY" // Might be same that builtin

# define CTX_PATH "PATH"
# define CTX_FILE "FILE"

# define CTX_ENV "ENV"
# define CTX_FLAG "FLAG"
# define CTX_DISCARD "DISCARD"



// TODO: Reset context with  "|;" and what else?
# define CTX_DISCARD_STR "|;<>-$"

static char *check_wo_moving_cursor(char buffer[INPUT_BUFFER], int cursor)
{
	if (!buffer || !cursor)
		return (CTX_BUILTIN);

	if (cursor > ft_strlen(buffer))
	{
		ft_printf("CURSOR > LEN");
		return (CTX_DISCARD);
	}

	if (buffer[cursor] == ' ' && buffer[cursor - 1] == ' ')
	{
		ft_printf("SPACES");
		return (CTX_DISCARD);
	}

	if (ft_strchr(CTX_DISCARD_STR, buffer[cursor]) && buffer[cursor] != '\0')
	{
		ft_printf("TOP OF CHAR");
		return (CTX_DISCARD);
	}

	return (NULL);
}

char *get_context(char buffer[INPUT_BUFFER], int cursor)
{
	char *ctx;

	if ((ctx = check_wo_moving_cursor(buffer, cursor)))
		return (ctx);

	// Discard extra spaces
	while (buffer[cursor] == ' ')
		cursor--;

	while (cursor && buffer[cursor] != ' ')
		cursor--;
	if (!cursor)
		return (CTX_BUILTIN);
	else if (buffer[cursor - 1] == '|' || buffer[cursor - 1] == ';')
		return (CTX_BUILTIN);
	else if (buffer[cursor + 1] == '|' || buffer[cursor + 1] == ';')
		return (CTX_BUILTIN);
	else if (buffer[cursor + 1] == '-')
		return (CTX_FLAG);
	else if (buffer[cursor + 1] == '/')
		return (CTX_PATH);
	else if (buffer[cursor + 1] == '$')
		return (CTX_ENV);
	else
		return (CTX_PATH);

	ft_printf("HAPPENDED");
	return (CTX_DISCARD);
}


char **autocomplete(char *ctx)
{

	char *example[] = {"echo", "cd", "ls", NULL};
	char **pp = example;
	char **arr = malloc(sizeof(char *) * 4);
	int i = 0;
	while (*pp)
	{
		arr[i] = malloc(sizeof(char) * ft_strlen(*pp));
		ft_strcpy(arr[i], *pp);
		i++;
		pp++;
	}
	return arr;
}

void handle_autocomplete(t_line *line)
{
	// if (!line->autocomplete)
	// 	return ;
	char *ctx = get_context(line->input, line->pos);
	if (ft_strcmp(ctx, CTX_DISCARD) == 0)
		return ;
	char **arr;
	arr = autocomplete(ctx);
	ft_printf("\n%s", arr[0]);
	ft_printf("\n%s", arr[1]);
	ft_printf("\n%s", arr[2]);

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
