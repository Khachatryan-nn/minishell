/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:50:46 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 23:37:45 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	putstr_fd(char *s, int t, int fd);
int	ft_putchar_fd(char c, int fd);

int	putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}

int	putstr_fd(char *s, int t, int fd)
{
	int	i;

	i = -1;
	if (!s)
		return (putstr_fd("(null)", 0, fd));
	while (s[++i] != '\0')
		ft_putchar_fd(s[i], fd);
	if (t == 1)
	{
		free (s);
		s = 0;
	}
	return (i);
}
