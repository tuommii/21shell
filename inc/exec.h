/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:09:50 by srouhe            #+#    #+#             */
/*   Updated: 2020/02/13 16:16:55 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define EXEC_OK 		0
# define EXEC_ERROR 	1
# define BUF_SIZE		4096

int						execution_init(t_ast *ast);
int						execute_command(t_ast *ast);
int						builtins(char **cmd);
char					**expand_tokens(t_ast *ast);

int						echo_builtin(char **args);
int						cd_builtin(char **args);
int						display_env(void);
int						find_env(char *var);
int						setenv_builtin(char **cmd);
int						unsetenv_builtin(char **args);

char					*get_env(char *var);
char					**realloc_arr(size_t size);
char					*parse_path(char *cwd);

void					set_env(char *key, char *value);

#endif
