/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/03 15:26:33 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// gcc autocomplete.c -I ../inc -I ../libft/

#include "stdio.h"
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
# define CTX_RESET "|;"

static char *check_params(char buffer[INPUT_BUFFER], int cursor)
{
	if (!buffer || !cursor)
		return (CTX_BUILTIN);

	if (cursor > strlen(buffer))
		return (CTX_DISCARD);

	if (buffer[cursor] == ' ' && buffer[cursor - 1] == ' ')
		return (CTX_DISCARD);

	return (NULL);
}

char *get_context(char buffer[INPUT_BUFFER], int cursor)
{
	char *ctx;

	if ((ctx = check_params(buffer, cursor)))
		return (ctx);

	// Discard extra spaces
	while (buffer[cursor] == ' ')
		cursor--;

	if (cursor && buffer[cursor - 1] == ' ')
	{
		// Cursor is top of $ or -
		// '/' is valid so not checking that
		if (buffer[cursor] == '$' || buffer[cursor] == '-')
			return (CTX_DISCARD);
	}

	while (cursor && buffer[cursor] != ' ')
		cursor--;
	if (!cursor)
		return (CTX_BUILTIN);
	else if (buffer[cursor + 1] == '-')
		return (CTX_FLAG);
	else if (buffer[cursor + 1] == '/')
		return (CTX_PATH);
	else if (buffer[cursor + 1] == '$')
		return (CTX_ENV);
	return (CTX_DISCARD);
}

int main() {

	char test[INPUT_BUFFER] = "ls  -all $HOME   /home";
	char test2[INPUT_BUFFER] = "echo  $HOME";

	int i = 0;
	while (i < strlen(test))
	{
		printf("cursor: %c, %s\n", test[i], get_context(test, i));
		i++;
	}
	return (0);
}
