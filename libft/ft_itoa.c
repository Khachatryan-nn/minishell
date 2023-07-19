/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:33:55 by musimony          #+#    #+#             */
/*   Updated: 2023/07/18 22:12:39 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_nb_digit(long n, int sign)
{
	unsigned int	nb_digit;

	if (n == 0)
		return (1);
	nb_digit = 0;
	while (n > 0)
	{
		n /= 10;
		nb_digit++;
	}
	if (sign == -1)
		nb_digit++;
	return (nb_digit);
}

static void	convert_nb(char *str, long n, unsigned int nb_digit,
		int sign)
{
	str[nb_digit] = '\0';
	str[--nb_digit] = n % 10 + '0';
	n /= 10;
	while (n > 0)
	{
		str[--nb_digit] = n % 10 + '0';
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*str;
	long			m;
	unsigned int	nb_digit;
	int				sign;

	sign = 1;
	if (n < 0)
	{
		m = (long)n * -1;
		sign = -1;
	}
	else
		m = n;
	nb_digit = get_nb_digit(m, sign);
	str = malloc(sizeof(char) * (nb_digit + 1));
	if (!str)
		return (NULL);
	convert_nb(str, m, nb_digit, sign);
	return (str);
}
