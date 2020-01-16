/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:53:12 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/16 11:19:52 by mtuomine         ###   ########.fr       */
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

void	print_prompt(t_input *input)
{
	static int started = 0;

	if (started)
		ft_printf("\n");
	started = 1;
	// char	host[INPUT_BUFFER + 1];
	//char	cwd[INPUT_BUFFER + 1];
	if (!input)
	{

	}
	char *logname = getenv("LOGNAME");
	// gethostname(host, INPUT_BUFFER);
	//getcwd(cwd, INPUT_BUFFER);
	ft_printf(FT_GREEN);
	ft_printf("%s", logname);

	// input->prompt_len += ft_strlen(logname);
	// input->prompt_len += ft_strlen(cwd);
	// input->prompt_len += 3;
	// prompt_len(input);


	// ft_printf("@");
	// ft_printf(FT_BOLD_BLUE);
	// ft_printf("%s: ", host);
	ft_printf(FT_RESET);
	ft_printf("%s", input->extra);
}
