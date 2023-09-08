/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:55:34 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/09 02:47:09 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int						check_exit_status(t_tok *stack, char **arr, char *s, \
																int exit_num);
int						mshell_exit(t_tok *stack, char **arr, t_env *env, \
																char *s);
int						exit_error_code(t_tok *stack, t_env *env, char *s);
void					pwd_init_2(t_env *my_env, char *str, int *i);
void					mshell_export(char **matrix, t_env *my_env);
void					export(char **matrix, int i, t_env *my_env);
int						mshell_unset(char **matrix, t_env *my_env);
void					mshell_cd(char **matrix, t_env *my_env);
int						check_built(t_tok *stack, t_env *env);
t_env					*env_init(char **env, t_env *my_env);
int						ft_check(t_env *my_env, char *str);
void					mshell_pwd(char *str, t_env *env);
void					ft_add(t_env *my_env, char *str);
void					mshell_echo(char **matrix);
void					ft_export(t_env *my_env);
void					pwd_init(t_env *my_env);
int						check_unset(char *str);
void					mshell_env(t_env *env);
char					*ft_itul(long long n);
char					*trim_zeroes(char *s);
void					call_signals(int sig);
unsigned long long int	ft_atll(char *str);

#endif