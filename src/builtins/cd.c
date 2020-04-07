/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:55:11 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/07 15:35:08 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		print_path(char *path)
{
	char	*tmp;

	tmp = parse_path(path);
	ft_putendl(tmp);
	free(tmp);
}

static int		move_to(char *path, int print)
{
	char	*cwd;
	char	*pwd;
	char	buffer[BUF_SIZE + 1];

	errno = 0;
	if (!chdir(path))
	{
		pwd = ft_strdup(getenv("PWD"));
		set_env("OLDPWD", pwd);
		cwd = getcwd(buffer, BUF_SIZE);
		set_env("PWD", cwd);
		print ? print_path(cwd) : PASS;
		free(pwd);
		return (EXEC_OK);
	}
	else
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			print_error(errno, path);
		else if (access(path, R_OK) == -1)
			print_error(errno, path);
		else
			print_error(errno, path);
		return (errno);
	}
}

static int		change_pwd(char **args)
{
	int		status;
	char	*cwd;

	cwd = ft_strdup(getenv("PWD"));
	if (args[2])
	{
		ft_putendl("cd: too many arguments");
		status = EXEC_ERROR;
	}
	else if (ft_strstr(cwd, args[0]))
	{
		cwd = ft_strreplace(cwd, args[0], args[1]);
		status = move_to(cwd, 1);
		free(cwd);
	}
	else
	{
		ft_printf("cd: string not in pwd: %s\n", args[0]);
		status = EXEC_ERROR;
	}
	free(cwd);
	return (status);
}

/*
**		Built in cd command.
**		Two args: modifies PWD variable and jumps into that directory.
*/

int				cd_builtin(char **args)
{
	char	*home;

	home = getenv("HOME");
	if (!args[0] || ft_strequ(args[0], getenv("USER"))
				|| ft_strequ(args[0], "--"))
	{
		if (home)
			return (move_to(home, 0));
		else
			return (EXEC_OK);
	}
	else if (args[0] && args[1])
		return (change_pwd(args));
	else if (ft_strequ(args[0], "-"))
		return (move_to(getenv("OLDPWD"), 1));
	else
		return (move_to(args[0], 0));
}
