/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:09:26 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/09 02:46:18 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

t_tok	*lstnew_pars(char *content, t_type type, int prec, int flag);
void	lstback_wcard(t_wcard **pars, t_wcard *new);
t_env	*push_back(t_env **list, t_env *new);
void	lstback(t_tok **lst, t_tok *new);
void	destroy_structure(t_tok *root);
void	lstclear_wcard(t_wcard **lst);
t_wcard	*lstlast_wcard(t_wcard *lst);
t_wcard	*lstadd_wcard(char *string);
int		lstsize_wcard(t_wcard *lst);
void	destroy_init(t_init *init);
t_tok	*ast_branch(t_tok *tok);
t_env	*malloc_list(char *env);
int		env_lstsize(t_env *lst);
void	lstclear(t_tok **lst);
t_tok	*lstlast(t_tok *lst);
int		lstsize(t_tok *lst);

#endif
