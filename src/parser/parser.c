/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/09 21:03:26 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd		*new_cmd(char **args)
{
	t_cmd	*new;

	if (!(new = ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	new->args = args;
	new->next = NULL;
	return (new);
}

/*
**	Create list of commands from lexer tokens
*/

void		add_command(t_token **head, t_cmd **cmd)
{
	int		i;
	int		size;
	char	**args;
	t_cmd	**tmp;

	i = 0;
	size = args_count(*head);
	args = (char **)ft_memalloc(size);
	// ft_printf("   token count [%d]", size);
	while (*head && (*head)->type & T_STR)
	{
		args[i] = ft_strdup((*head)->data);
		// ft_printf("   str token [%s]", head->data);
		*head = (*head)->next;
		i++;
	}
	// Check operators & redirections here
	args[i] = NULL;
	tmp = cmd;
	while (*tmp)
		*tmp = (*tmp)->next;
	*tmp = new_cmd(args);
}

void	parse_commands(t_lexer **lexer, t_cmd **cmd)
{
	t_token	*head;

	head = (*lexer)->head;
	// while (head)
	// {
	add_command(&head, cmd);
	// ft_printf("\thead data: [%s]", head->data);
		// head = head->next;
	// }
}

/*
**	1 - check lexer
**	2 - check syntax
*/

t_cmd		*parser(t_lexer **lexer)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!lexer || !*lexer || !(*lexer)->count)
		return (NULL);
	else if (check_syntax(*lexer) == PARSER_ERROR)
		return (NULL);
	parse_commands(lexer, &cmd);
	return (cmd);
}
