/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:09:50 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/16 13:11:30 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define EXEC_OK 		0
# define EXEC_ERROR 	256
# define PIPE_EXEC		512
# define NORMAL_EXEC	1024
# define BUF_SIZE		4096

int						execution_init(t_ast *ast);
int						execute_command(t_ast *ast, int exec_type);
int						execute_pipeline(t_ast *left, t_ast *right);
int						pipe21(char *path, char **args);
int						init_redirection(t_ast *ast);
int						open_file(t_token *token);
int						exec_status(int status);
int						exec_preprocess(int save[3], t_ast *ast);
int						dup21(int dst, int src, char *msg);
int						pipe_heredoc(t_token *dlarr);
int                     copy_to_clipboard(char *input);

int						is_builtin(char *cmd);
int						exec_builtin(char **cmd);
int						echo_builtin(char **args);
int						cd_builtin(char **args);
int						display_env(void);
int						find_env(char *var);
int						setenv_builtin(char **cmd);
int						unsetenv_builtin(char **args);

char					*get_env(char *var);
char					*parse_path(char *cwd);
char					**realloc_arr(size_t size);
char					**tokens_to_tab(t_ast *ast);

void					set_env(char *key, char *value);
void					restore_fd(t_ast *ast, int save[3]);

#endif
