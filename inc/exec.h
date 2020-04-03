/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:09:50 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/03 12:44:27 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define EXEC_OK 		0
# define EXEC_ERROR 	1
# define BUF_SIZE		4096

int						execution_init(t_ast *ast);
int						execute_command(t_ast *ast);
int						init_pipeline(t_ast *left, t_ast *right);
int						init_redirection(t_ast *ast);
int						builtins(char **cmd);
int						open_file(t_token *token);

int						echo_builtin(char **args);
int						cd_builtin(char **args);
int						display_env(void);
int						find_env(char *var);
int						setenv_builtin(char **cmd);
int						unsetenv_builtin(char **args);

char					*get_env(char *var);
char					**realloc_arr(size_t size);
char					*parse_path(char *cwd);
char					**expand_tokens(t_ast *ast);

void					set_env(char *key, char *value);
void					restore_fd(t_ast *ast, int save[3]);

#endif
