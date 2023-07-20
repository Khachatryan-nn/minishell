/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:59:10 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/18 22:07:48 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_percentage(char type, va_list arg)
{
	if (type == 'c')
		return (ft_putchr(va_arg(arg, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(arg, char *), 0));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(arg, int)));
	else if (type == 'u')
		return (ft_putnbrun(va_arg(arg, unsigned int)));
	else if (type == 'x' || type == 'X')
		return (ft_putnbrhex(va_arg(arg, unsigned int), type));
	else if (type == 'p')
		return (ft_putptrhex(va_arg(arg, char *)));
	else if (type == '%')
		return (ft_putchr('%'));
	return (0);
}

int	ft_printf(const char *arg, ...)
{
	int		len;
	int		i;
	va_list	args;

	i = 0;
	len = 0;
	if (!arg)
		return (0);
	va_start(args, arg);
	while (arg[i])
	{
		while (arg[i] != '%' && arg[i] != '\0' && ++len)
			write (1, &arg[i++], 1);
		if (arg[i] == '%')
		{
			i++;
			len += ft_percentage (arg[i++], args);
		}
	}
	va_end(args);
	return (len);
}
