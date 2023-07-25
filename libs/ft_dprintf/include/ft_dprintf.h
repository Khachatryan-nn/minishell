/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:19:13 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 23:37:41 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_percentage(int fd, char type, va_list arg);
int		ft_putnbrhex(int fd, unsigned int nb, char c);
int		ft_dprintf(int fd, const char *arg, ...);
int		ft_putptrhex(int fd, char const *ptr);
int		ft_putnbrun(int fd, unsigned int nb);
char	*ft_itoahex(unsigned int n, char c);
int		putstr_fd(char *s, int t, int fd);
char	*ft_itoaptrhex(uintptr_t n);
int		putchar_fd(char c, int fd);
char	*ft_itoaun(unsigned int n);
int		ft_putnbr(int fd, int nb);
char	*ft_itoa(int n);

#endif