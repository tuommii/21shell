/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:35:40 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/17 18:25:00 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Should we write history to file so its permanent
// Search autocompletions after tabpress

/*
`cl'
String of commands to clear the entire screen and position the cursor at the upper left corner.
`cd'
String of commands to clear the line the cursor is on, and all the lines below it, down to the bottom of the screen. This command string should be used only with the cursor in column zero; their effect is undefined if the cursor is elsewhere.
`ce'
String of commands to clear from the cursor to the end of the current line.
`ec'
String of commands to clear n characters, starting with the character that the cursor is on. This command string is expected to leave the cursor position unchanged. The parameter n should never be large enough to reach past the right margin; the effect of such a large parameter would be undefined.
*/
#include "shell.h"
