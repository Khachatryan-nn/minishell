/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:00:04 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 21:14:43 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ETC_H
# define ETC_H

# include "defines.h"

void	wcard_logic_2(char **pattern, char **string, int star);
char	*expand(char *str, t_env *env, t_exp *exp);
int		wcard_logic(char *pattern, char *string);
void	get_file(char *path, t_wcard **wcard);
void	do_expand(t_tok *stack, t_env *env);
void	exp_2(t_exp **tmp, t_env *env);
void	destroy_exp(t_exp *exp);
int		onlydollar(char *str);
void	exp_1(t_exp **tmp);
void	exp_3(t_exp **tmp);

#endif
