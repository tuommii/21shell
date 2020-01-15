/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:25 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 20:13:54 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <term.h>
// # include <termios.h>
// # include <termio.h>

#include "../libft/libft.h"
#include "setup.h"

# define KEYBOARD_BUFF_LEN 4
# define OUTPUT STDIN_FILENO

int g_kill;

#endif
