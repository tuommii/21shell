/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:53:12 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 17:28:37 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		startup_banner(void)
{
	int		fd;
	char	*line;

	if ((fd = open(".boot", O_RDWR)) < 0)
		return ;
	while (get_next_line(fd, &line))
		ft_putendl_fd(line, OUTPUT);
	close(fd);
}

void	print_prompt(t_shell *shell)
{
	// char	host[shell_BUFFER + 1];
	//char	cwd[shell_BUFFER + 1];
	if (!shell)
	{

	}
	char *logname = getenv("LOGNAME");
	// gethostname(host, shell_BUFFER);
	//getcwd(cwd, shell_BUFFER);
	ft_printf(FT_GREEN);
	ft_printf("%s", logname);

	// shell->prompt_len += ft_strlen(logname);
	// shell->prompt_len += ft_strlen(cwd);
	// shell->prompt_len += 3;
	// prompt_len(shell);


	// ft_printf("@");
	// ft_printf(FT_BOLD_BLUE);
	// ft_printf("%s: ", host);
	ft_printf(FT_RESET);
	ft_printf("%s", shell->extra);
}
