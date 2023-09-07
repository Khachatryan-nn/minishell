/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:09:46 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 21:11:09 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
 # define UTILS_H

void	handle_heredoc_input(t_init *init, t_tok *tok, char *str);
char	*strjoin_helper(char *result, char *read, int mode);
int		_free3_(char *ptr1, char **ptr2, char **ptr3);
void	builtins_error(char	*str, char *err);
int		ft_strcmp(char *s1, char *s2);
int		matrixlen(char **matrix);
void	free_matrix(char **ptr);
int		check_digit(char *str);
void	leaks_check(void);

#endif