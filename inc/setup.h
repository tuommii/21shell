/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:00:15 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 20:13:34 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

#include <termio.h>

#define OUTPUT STDIN_FILENO

int g_kill;

void	config_terminal(int reset);
void	check_terminal_config(void);
int		print_char(int c);

void		listen_signals(void);
void		watch_kill();

void		startup_banner(void);


#endif
