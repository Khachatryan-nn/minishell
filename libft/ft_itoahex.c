/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoahex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:09:40 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/18 22:09:56 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenght(unsigned int n)
{
	int	k;

	k = 0;
	while (n != 0)
	{
		n /= 16;
		k++;
	}
	return (k);
}

static char	ft_chr(unsigned int n, int lenght, char c)
{
	while (--lenght)
		n /= 16;
	n %= 16;
	if (n < 0)
		n *= -1;
	if (n > 9 && c == 'x')
		return (97 + n % 10);
	else if (n > 9 && c == 'X')
		return (65 + n % 10);
	return (n + '0');
}

char	*ft_itoahex(unsigned int n, char c)
{
	char	*p;
	int		i;
	int		lenght;

	i = 0;
	if (n == 0)
		lenght = 1;
	else
		lenght = ft_lenght(n);
	p = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!p)
		return (0);
	while (lenght)
		p[i++] = ft_chr(n, lenght--, c);
	p[i] = '\0';
	return (p);
}
