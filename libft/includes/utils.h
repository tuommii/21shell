/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:33:06 by srouhe            #+#    #+#             */
/*   Updated: 2020/01/15 19:10:17 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define BUFF_SIZE 32000

# include "libft.h"

int		matchhere(char *regexp, char *s);
int		matchstar(int c, char *regexp, char *s);

#endif
