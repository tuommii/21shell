/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:02:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 17:14:24 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(int argc, char **argv, char **environment)
{
	if (!argc || !argv || !environment)
		exit(EXIT_FAILURE);
	write(1, "Hello from 21shell!\n", 20);
	exit(EXIT_SUCCESS);
}
