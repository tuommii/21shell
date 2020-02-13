/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:03:38 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 15:40:57 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**expand_tokens(t_ast *ast)
{
	int		i;
	char	**cmd;

	if (!(cmd = (char **)malloc(sizeof(char *) * (ast->nbr_token + 1))))
		return (NULL);
	i = 0;
	while (ast->token != ast->cmd_end)
	{
		cmd[i] = ft_strdup(ast->token->data);
		ast->token = ast->token->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

// int		builtins(char **cmd, t_shell *sh)
// {
// 	if (ft_strequ(cmd[0], "exit"))
// 		return (-1);
// 	else if (ft_strequ(cmd[0], "echo"))
// 		return (echo_builtin(cmd + 1));
	// else if (ft_strequ(cmd[0], "cd"))
	// 	return (cd_builtin(cmd + 1, sh));
	// else if (ft_strequ(cmd[0], "setenv"))
	// 	return (setenv_builtin(cmd + 1, sh));
	// else if (ft_strequ(cmd[0], "unsetenv"))
	// 	return (unsetenv_builtin(cmd + 1, sh));
	// else if (ft_strequ(cmd[0], "env"))
	// 	return (display_env(sh));
// 	return (0);
// }
