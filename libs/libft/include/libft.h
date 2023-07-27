/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:23:02 by musimony          #+#    #+#             */
/*   Updated: 2023/07/27 16:36:53 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
// # include "minishell.h"

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char	*ptr;
	char	*value;
	int		type;
	int		flag;
	void	*content;
}			t_list;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
// int		ft_strcmp(const char *s1, const char *s2, int n);
char	*ft_strnstr( char *str, char *str1, int len);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strrchr(const char *str, int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nitems, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_getstart(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2, int mode);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));

#endif
