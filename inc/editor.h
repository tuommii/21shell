/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:21:19 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/15 23:31:55 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# define INPUT_BUFFER 4096

typedef struct	s_editor
{
				int x;
				int y;
				int i;
				char input[INPUT_BUFFER];
}				t_editor;

t_editor *create_editor(void);

#endif
