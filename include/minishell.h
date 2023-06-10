/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/06/08 18:17:45 by musimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


typedef struct s_list
{
    char *ptr;
    void *next;
    void *prev;
    void *content;
}   t_list;


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

// char	**ft_split(const char *s, char c);
// int	ft_size_word(char const *s, char c, int i);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// size_t	ft_strlen(const char *str);
// char	*ft_strdup(const char *s1);
// int	ft_strcmp(const char *s1, const char *s2);
// int chdir(const char *str);
void    ft_pwd(t_list *env);
void    ft_create_env(char **str, t_list **stack);
void    ft_env(t_list *env);
t_list *ft_lstnew_2(char *str);
void    ft_cd(t_list *str, char *text);
char    *ft_change_str(char *str);
// char *read_line(const char *str);

#endif
