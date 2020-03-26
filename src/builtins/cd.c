/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:55:11 by srouhe            #+#    #+#             */
/*   Updated: 2020/03/26 11:42:21 by srouhe           ###   ########.fr       */
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

static void		move_to(char *path, int print)
{
	char	*cwd;
	char	*pwd;
	char	buffer[BUF_SIZE + 1];

	if (!chdir(path))
	{
		pwd = ft_strdup(getenv("PWD"));
		set_env("OLDPWD", pwd);
		cwd = getcwd(buffer, BUF_SIZE);
		set_env("PWD", cwd);
		print ? print_path(cwd) : PASS;
		free(pwd);
	}
	else
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			print_error(NOT_FOUND_ERR, path);
		else if (access(path, R_OK) == -1)
			print_error(PERMISSION_ERR, path);
		else
			print_error(NOT_DIR_ERR, path);
	}
}

void			change_pwd(char **args)
{
	char	*cwd;

	cwd = ft_strdup(getenv("PWD"));
	if (args[2])
		ft_putendl("cd: too many arguments");
	else if (ft_strstr(cwd, args[0]))
	{
		cwd = ft_strreplace(cwd, args[0], args[1]);
		move_to(cwd, 1);
		free(cwd);
	}
	else
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(args[0]);
	}
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
			move_to(home, 0);
		else
			return (EXEC_OK);
	}
	else if (args[0] && args[1])
		change_pwd(args);
	else if (ft_strequ(args[0], "-"))
		move_to(getenv("OLDPWD"), 1);
	else
		move_to(args[0], 0);
	return (EXEC_OK);
}
