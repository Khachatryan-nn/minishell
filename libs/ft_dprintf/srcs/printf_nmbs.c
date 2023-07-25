/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_nmbs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:10:09 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 23:37:11 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_putnbr(int fd, int nb)
{
	return (putstr_fd(ft_itoa(nb), 1, fd));
}

int	ft_putnbrun(int fd, unsigned int nb)
{
	return (putstr_fd(ft_itoaun(nb), 1, fd));
}

int	ft_putnbrhex(int fd, unsigned int nb, char c)
{
	return (putstr_fd(ft_itoahex(nb, c), 1, fd));
}

int	ft_putptrhex(int fd, char const *ptr)
{
	write (fd, "0x", 2);
	return (putstr_fd(ft_itoaptrhex((uintptr_t) ptr), 1, fd) + 2);
}
