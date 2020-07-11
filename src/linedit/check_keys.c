/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 10:27:19 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/11 16:23:02 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linedit.h"

int	check_arrow_keys(t_line *line)
{
	if (line->key == LEFT)
	{
		return (handle_left_key(line));
	}
	else if (line->key == RIGHT)
	{
		return (handle_right_key(line));
	}
	else if (line->key == UP)
	{
		return (hist_next(line));
	}
	else if (line->key == DOWN)
	{
		return (hist_prev(line));
	}
	return (0);
}

int	check_command_keys(t_line *line)
{
	if (line->key == TAB)
		return (handle_autocomplete(line));
	else if (line->key == BACKSPACE)
		return (handle_backspace(line));
	return (0);
}

int	check_ctrl_arrow_keys(t_line *line)
{
	if (line->key == CTRL_LEFT)
		return (goto_prev_word(line));
	else if (line->key == CTRL_RIGHT)
		return (goto_next_word(line));
	else if (line->key == CTRL_UP)
		return (goto_row_up(line));
	else if (line->key == CTRL_DOWN)
		return (goto_row_down(line));
	return (0);
}


static int join( char *com1[], char *com2[], char **envp)
{
    int p[2];       /* pipe */
    int status;     /* status */

    /* create child to run commands */
    switch( fork() )
    {
        case -1:
            /* fork was unsuccessful */
            ft_putstr("unable to fork!\n");
            return( -1 );

        case 0:
            /* child process */
            break;

        default:
            /* parent process */
            wait(&status);
            return (status);
    }

    /* remainder of routine executed by child */

    /* create pipe */
    if (pipe(p) < 0) /* can use 'p' since address */
    {
        ft_putstr("unable to pipe!\n" );
        return(-1);
    }

	// Error otherwise ?
	// char *envp[2] = {"$DISPLAY=:0", 0};
    /* create another process */
    switch( fork() )
    {
        case -1:
            /* fork was unsuccessful */
            ft_putstr("unable to fork!\n");
            return (-1);

        case 0:
            /* child process */
            close(1);    /* close standard output */

            /* make standard output go to pipe */
            dup(p[1]);

            close(p[0]);       /* close file descriptors */
            close(p[1]);

            /* execute command 1 */
			// ft_printf("\nENV%s\n", envs[0]);
			execve("/bin/echo", com1, envp);
            // execvp( com1[0], com1 );

            /* if execvp returns, error occured */
            ft_putstr("first execvp call failed!\n");
            return( -1 );

        default:
            /* parent process */
            close(0);     /* close standard input */

            /* make standard input come from pipe */
            dup(p[0]);

            close(p[0]);       /* close file descriptors */
            close(p[1]);

            /* execute command 2 */
			execve("/usr/bin/xclip", com2, envp);
            // execvp( com2[0], com2 );

            /* if execvp returns, error occured */
            ft_putstr("second execvp call failed!\n");
            return (-1);
    }
}



int	check_copy_paste_del(t_line *line)
{
	if (line->key == DELETE || (line->key == CTRL_D && line->len))
		return (handle_delete(line));
	else if (line->key == CTRL_P)
	{
		external_paste(&line->clipboard);
		clipboard_draw(line);
		return (1);
	}
	else if (line->key == CTRL_W)
		return (cut_to_start(line));
	else if (line->key == CTRL_A)
		return (yank(line));
	else if (line->key == CTRL_E)
		return (cut_to_end(line));
	else if (line->key == CTRL_K)
	{
		char *eka[3];
		char *toka[4];


		eka[0] = "echo";
		eka[1] = "-n";
		eka[2] = line->input;
		eka[3] = (char *)0;

		toka[0] = "xclip";
		toka[1] = "-selection";
		toka[2] = "clipboard";
		toka[3] = (char *)0;

		// int a[2];

		// write(a[1], line->input, ft_strlen(line->input));
		join(eka, toka, line->envp);

		// ft_printf("\nCOPY\n");
		return (1);
	}
	return (0);
}

int	check_terminating_keys(t_line *line)
{
	if (line->key == ESC || (line->key == CTRL_D && !line->len))
	{
		toggle_raw(1, 0);
		return (1);
	}
	return (0);
}
