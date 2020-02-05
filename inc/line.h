/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:56:24 by mtuomine          #+#    #+#             */
/*   Updated: 2020/02/05 17:58:16 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# define INPUT_BUFFER 4096

typedef struct s_line
{
				char input[INPUT_BUFFER];
				// Cursor
				int x;
				int y;
				// Index
				int i;
				// sh len
				int len;
				// terminal columns & rows
				int rows;
				int cols;
				// Prompt data
				char *username;
				char *extra;
				int prompt_len;
				int username_len;
				int extra_len;
				// Key pressed
				int key;
} t_line;


#endif
