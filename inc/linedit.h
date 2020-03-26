/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:34:56 by mtuomine          #+#    #+#             */
/*   Updated: 2020/03/26 12:42:32 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEDIT_H
# define LINEDIT_H

# include <stdlib.h>
# include <stdio.h>			// TODO: For debugging func
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <term.h>
# include <unistd.h>

#include "libft.h"

# define INPUT_BUFFER 4096
# define OUTPUT STDOUT_FILENO
// TODE: This is so small just for testing purposes
# define MAX_HISTORY 3

/*
** Linux support
*/
# ifndef TIOCGSIZE
#  define TIOCGSIZE TIOCGWINSZ
# endif

// KEYBOARD
# define KEYBOARD_BUFFER 6
# define TAB 9
# define ENTER 10
# define ESC 27
# define LEFT 186
# define UP 183
# define RIGHT 185
# define DOWN 184
# define BACKSPACE 127
# define DELETE 295

# define CTRL_D 4
# define CTRL_C 0
# define CTRL_L 12

// TODO: Paste
# define CTRL_P 16
# define CTRL_K 11
# define CTRL_X 24

# define CTRL_LEFT 347
# define CTRL_RIGHT 346
# define CTRL_DOWN 345
# define CTRL_UP 344

# define HOME_KEY 190
# define END_KEY 188


typedef struct s_suggestions
{
	int len;
	char **arr;
} t_suggestions;

typedef void(autocomp_cb)(const char *, t_suggestions *);


typedef struct s_line
{
	char		input[INPUT_BUFFER + 1];
	char		debug[INPUT_BUFFER + 1];
	char		clipboard[INPUT_BUFFER + 1];
	char		*prompt;
	int			len;
	int			prompt_len;
	int			key;
	int			pos;
	int			old_pos;
	int			lines_used;
	int			cols;
	struct		s_hist *hist;
	int			hist_count;
	int			hist_i;
	int			is_cut;
	int			cut_start;
	int			cut_end;
	int			cut_running;
	int			copy_running;
	int			copy_start;
	int			copy_end;
	struct s_suggestions suggestions;
	autocomp_cb *cb;

} t_line;

typedef struct s_hist
{
	char *str;
	int i;
	struct s_hist *prev;
	struct s_hist *next;
} t_hist;

int g_kill;



void linedit_completion_cb(t_line *line, autocomp_cb *cb);




void	linedit_setup(void);
//void	linedit_start(void);
void	linedit_config(int reset);


int 	get_cols(void);
void	redraw_input(t_line *line);

void clear_rows(t_line *line);

// UTILS
int		print_char(int c);
int is_empty(char *str);
void free_history(t_hist **hist);




int copy_cat(t_line *line, int is_cut, int *state, int *start);
void paste(t_line *line);

int which_action(t_line *line);

// CHECK KEYS
int	check_arrow_keys(t_line *line);
int	check_command_keys(t_line *line);
int	check_ctrl_arrow_keys(t_line *line);
int	check_copy_paste_del(t_line *line);
int	check_terminating_keys(t_line *line);

// SIGNALS
void		listen_signals(void);
void		watch_kill(t_line *line);



// KEYBOARD
int	keypress(void);
int handle_right_key(t_line *line);
int handle_left_key(t_line *line);
int handle_backspace(t_line *line);
int handle_delete(t_line *line);



void print_prompt(t_line *line);

t_line *create_line_editor(void);
/*
** Main function. Returns input
*/
char	*linedit(t_line *line);
void	linedit_exit(t_line *line);



/*
** HISTORY
*/
int	hist_append(t_hist **head, char *str);
void hist_print(t_hist *node);
t_hist *hist_pop(t_hist **head, int index);


/* HIST ACTION */
void hist_prev(t_line *line);
void hist_next(t_line *line);

/* GOTO ACTION */
void goto_end(t_line *line);
void goto_begin(t_line *line);
void goto_row_down(t_line *line);
void goto_row_up(t_line *line);
void goto_prev_word(t_line *line);
void goto_next_word(t_line *line);

void erase_input(t_line *line);
void clear_rows(t_line *line);

void reposition(t_line *line);
void apped_or_insert(t_line *line, char c);









#endif
