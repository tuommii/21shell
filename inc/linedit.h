/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:34:56 by mtuomine          #+#    #+#             */
/*   Updated: 2020/07/07 08:56:44 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEDIT_H
# define LINEDIT_H

# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <term.h>
# include <unistd.h>

# include "libft.h"

# define INPUT_BUFFER 4096
# define MAX_MATCHES 10
# define OUTPUT STDOUT_FILENO
# define MAX_HISTORY 3

/*
** Linux support
*/
# ifndef TIOCGSIZE
#  define TIOCGSIZE TIOCGWINSZ
# endif

# ifdef __APPLE__
#  define COPY_CMD "pbaste"
#  define COPY_PATH "/usr/bin/pbpaste"
#  define COPY_PARAM ""
# elif __linux__
#  define COPY_CMD "xclip"
#  define COPY_PATH "/usr/bin/xclip"
#  define COPY_PARAM "-o"
# endif

# ifdef __APPLE__
#  define COPY " | pbpaste"
# elif __linux__
#  define COPY " | xclip -sel clip"
# endif



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

# define CTRL_A 1
# define CTRL_E 5
# define CTRL_P 16
# define CTRL_K 11
# define CTRL_X 24
# define CTRL_W 23
# define CTRL_Y 25
# define CTRL_U 21

# define CTRL_LEFT 347
# define CTRL_RIGHT 346
# define CTRL_DOWN 345
# define CTRL_UP 344

# define HOME_KEY 190
# define END_KEY 188


// TODO: Enum?
# define CTX_EXEC "EXEC"
# define CTX_FLAG "FLAG"
# define CTX_PATH "PATH"
# define CTX_ENV "ENV"
# define CTX_DISCARD "DISCARD"



// TODO: Reset context with  "|;" and what else?
# define CTX_DISCARD_STR "|;<>-$"
# define MAX_MATCHES 10

typedef struct				s_completer
{
	char					**suggestions;
	// Suggestions count
	int						count;

	char					*matches[MAX_MATCHES];
	int 					matches_count;
	int 					len;
	char					*ctx;
	int						i;
	char					*word;
}							t_completer;

// typedef char				**(t_autocomp_cb)(const char *ctx);

typedef struct				s_clipboard {
	char					content[INPUT_BUFFER + 1];
}							t_clipboard;

typedef struct				s_hist
{
	char					*str;
	int						i;
	struct s_hist			*prev;
	struct s_hist			*next;
}							t_hist;

typedef struct				s_line
{
	char					input[INPUT_BUFFER + 1];
	char					cpy[INPUT_BUFFER + 1];
	char					internal[INPUT_BUFFER +1];
	int						len;
	char					*prompt;
	int						prompt_len;
	int						key;
	int						pos;
	int						old_pos;
	int						lines_used;
	int						cols;
	int						was_copy;
	int						is_cut;
	struct s_hist			*hist;
	int						hist_count;
	int						hist_i;
	char 					**envs;

	// struct s_suggestions	suggestions;
	// t_autocomp_cb			*autocomplete;

	struct s_clipboard		clipboard;
}							t_line;

int							g_kill;
int							g_cont;
int							g_was_copy;

char						*read_more(t_line *line, int nl_flag);
// void						linedit_completion_cb \
(t_line *line, t_autocomp_cb *cb);
void						clipboard_update(t_clipboard *clip);
void						clipboard_draw(t_line *line);
void						linedit_setup(void);
void						toggle_raw(int reset, int save_old);
int							get_cols(void);
void						redraw_input(t_line *line);
void						clear_rows(t_line *line);
int							print_char(int c);
int							is_empty(char *str);
void						free_history(t_hist **hist);
int							which_action(t_line *line);
int							check_arrow_keys(t_line *line);
int							check_command_keys(t_line *line);
int							check_ctrl_arrow_keys(t_line *line);
int							check_copy_paste_del(t_line *line);
int							check_terminating_keys(t_line *line);
void						listen_signals(void);
void						watch_kill(t_line *line);
int							keypress(void);
int							handle_right_key(t_line *line);
int							handle_left_key(t_line *line);
int							handle_backspace(t_line *line);
int							handle_delete(t_line *line);
void						print_prompt(t_line *line);
t_line						*create_line_editor(void);

char						*linedit(t_line *line);

/*
** HISTORY
*/

int							hist_append(t_hist **head, char *str);
void						hist_print(t_hist *node);
t_hist						*hist_pop(t_hist **head, int index);
void						hist_prev(t_line *line);
void						hist_next(t_line *line);

/*
** GOTO
*/

void						goto_end(t_line *line);
void						goto_begin(t_line *line);
void						goto_row_down(t_line *line);
void						goto_row_up(t_line *line);
void						goto_prev_word(t_line *line);
void						goto_next_word(t_line *line);
void						erase_input(t_line *line);
void						clear_rows(t_line *line);
void						reposition(t_line *line);
void						apped_or_insert(t_line *line, char c);

/*
** AUTOCOMPLETE
*/
void handle_autocomplete(t_line *line);
void get_completions(t_completer *ac);
void get_binaries(char  **envs);
char	**init_env(char **env);


int suggestions_env(t_line *line, t_completer **ac);
char		*ft_getenv(char *name, char **envs);


/*
** AC buffer
*/
char *get_word_at(char buffer[INPUT_BUFFER], int cursor);
void	delete_word(t_line *line, char *word);
void	insert_word(t_line *line, char *word);

/*
** AC filter
*/
char *get_context(char buffer[INPUT_BUFFER], int cursor);
void filter(t_completer *ac);
void sort_by_length(t_completer *ac);

/*
** AC clean
*/
void ac_clean_suggestions(t_completer *ac);
void ac_clean_matches(t_completer *ac);
void ac_clean_rest(t_completer *ac);
void ac_clean(t_completer *ac);




#endif
