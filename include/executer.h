/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:50:41 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/14 01:20:19 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "defines.h"

char	**alloc_cmd_matrix(char **matrix, char *cmd, t_wcard *wild, int *i);
char	**alloc_wc_matrix(char **matrix, t_tok *stack, t_wcard **wcard);
int		destroy_cmd(char *cmd, char **cmd_matrix, char **env_matrix);
int		right_branch(t_init *in, t_tok *s, t_env *env, int status);
int		left_branch(t_init *in, t_tok *s, t_env *env, int status);
int		pipe_prepair(t_init *init, t_tok *stack, t_env *env);
int		to_execute(t_init *init, t_tok *stack, t_env *env);
int		exec_iocmd(t_init *init, t_tok *stack, t_env *env);
int		call_cmd(t_init *init, t_tok *stack, t_env *env);
char	*check_cmd(t_tok *stack, char *cmd, char **path);
int		io_backup(int stdin_backup, int stdout_backup);
int		ch_reds(t_init *init, t_tok *stack, int mode);
void	fill_wc_matrix(t_tok *stack, t_wcard **wild);
void	handle_dollar(int exit_status, t_env *env);
char	**restore_cmd_line(t_tok *stack, int i);
int		_close3_(int fd1, int fd2, int fd3);
void	find_path(t_init *init, t_env *env);
int		io_dup2(int _stdin, int _stdout);
void	config_right_dups(t_tok *stack);
void	config_left_dups(t_tok *stack);
int		_close2_(int fd1, int fd2);
void	save_backup(t_init *init);
int		check_subsh(t_tok *stack);
int		error_code(int error_num);
char	**env_matrix(t_env *env);
int		close_pipes(int *fd);
void	init_hd(t_hd **hd);
int		_close_(int fd);

#endif
