/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:36:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/03 14:38:15 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// gcc autocomplete.c -I ../inc -I ../libft/

#include "stdio.h"
#include "linedit.h"

// TODO: Enum?
# define CTX_BUILTIN "BUILTIN"
# define CTX_BINARY "BINARY"
# define CTX_PATH "PATH"
# define CTX_FILE "FILE"
# define CTX_ENV "ENV"
# define CTX_FLAG "FLAG"
# define CTX_DISCARD "DISCARD"


char *get_context(char buffer[INPUT_BUFFER], int cursor)
{
	if (!buffer || !cursor)
		return (CTX_BUILTIN);

	if (cursor > INPUT_BUFFER)
		return (CTX_DISCARD);

	// Discard extra spaces
	while (buffer[cursor] == ' ')
		cursor--;

	if (cursor && buffer[cursor - 1] == ' ')
	{
		// Cursor is top of $ or -
		if (buffer[cursor] == '$' || buffer[cursor] == '-')
			return (CTX_DISCARD);
	}

	while (cursor && buffer[cursor] != ' ')
		cursor--;
	if (!cursor)
		return (CTX_BUILTIN);
	else if (buffer[cursor + 1] == '-')
		return (CTX_FLAG);
	else if (buffer[cursor + 1] == '$')
		return (CTX_ENV);
	return (CTX_DISCARD);
}

int main() {

	char test[INPUT_BUFFER] = "ls  -a $HOME";
	printf("%s\n", get_context(test, 0));
	printf("%s\n", get_context(test, 1));
	printf("%s\n", get_context(test, 2));
	printf("%s\n", get_context(test, 3));
	printf("==============================\n");
	printf("%s\n", get_context(test, 4));
	printf("==============================\n");
	printf("%s\n", get_context(test, 5));
	printf("%s\n", get_context(test, 6));
	printf("==============================\n");
	printf("%s\n", get_context(test, 7));
	printf("==============================\n");
	printf("%s\n", get_context(test, 8));
	printf("%s\n", get_context(test, 9));
	printf("%s\n", get_context(test, 10));
	printf("%s\n", get_context(test, 11));
	printf("%s\n", get_context(test, 12));

	return (0);
}
