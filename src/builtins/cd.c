/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:55:11 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 16:05:24 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "exec.h"

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
		pwd = ft_strdup(get_env("PWD"));
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
			ft_putstr("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putendl(path);
	}
}

void			change_pwd(char **args)
{
	char	*cwd;

	cwd = ft_strdup(get_env("PWD"));
	if (args[2])
	{
		ft_putendl("cd: too many arguments");
	}
	else if (ft_strstr(cwd, args[0]))
	{
		cwd = ft_str_replace(cwd, args[0], args[1]);
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

	home = get_env("HOME");
	if (!args[0] || ft_strequ(args[0], get_env("USER"))
				|| ft_strequ(args[0], "--"))
	{
		if (home)
			move_to(home, 0);
		else
			return (1);
	}
	else if (args[0] && args[1])
		change_pwd(args);
	else if (ft_strequ(args[0], "-"))
		move_to(get_env("OLDPWD"), 1);
	else
		move_to(args[0], 0);
	return (1);
}
