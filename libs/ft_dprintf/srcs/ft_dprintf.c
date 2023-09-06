/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:33:20 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/06 16:24:32 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_percentage(int fd, char type, va_list arg)
{
	if (type == 'c')
		return (putchar_fd(va_arg(arg, int), fd));
	else if (type == 's')
		return (putstr_fd(va_arg(arg, char *), 0, fd));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(fd, va_arg(arg, int)));
	else if (type == 'u')
		return (ft_putnbrun(fd, va_arg(arg, unsigned int)));
	else if (type == 'x' || type == 'X')
		return (ft_putnbrhex(fd, va_arg(arg, unsigned int), type));
	else if (type == 'p')
		return (ft_putptrhex(fd, va_arg(arg, char *)));
	else if (type == '%')
		return (putchar_fd('%', fd));
	return (0);
}

int	ft_dprintf(int fd, const char *arg, ...)
{
	int		len;
	int		i;
	va_list	args;

	i = 0;
	len = 0;
	if (!arg || fd < 0)
		return (0);
	va_start(args, arg);
	while (arg[i])
	{
		while (arg[i] != '%' && arg[i] != '\0' && ++len)
			write (1, &arg[i++], 1);
		if (arg[i] == '%')
		{
			i++;
			len += ft_percentage (fd, arg[i++], args);
		}
	}
	va_end(args);
	return (len);
}
