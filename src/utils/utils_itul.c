/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_itul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:48:42 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/13 22:07:06 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itul(long long n);

static	int	digit_count(long long n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*zerocase(char *m)
{
	m = (char *)malloc(sizeof(char) * 2);
	m[0] = 0 + '0';
	m[1] = 0;
	return (m);
}

static char	*line(int len, char *p, long long n)
{
	unsigned long long	a;

	p[len] = '\0';
	len--;
	if (n < 0)
	{
		p[0] = '-';
		a = (unsigned long long)(n * -1);
		while (a != 0)
		{
			p[len--] = (a % 10) + '0';
			a /= 10;
		}
	}
	else
	{
		while (n != 0)
		{
			p[len--] = (n % 10) + '0';
			n /= 10;
		}
	}
	return (p);
}

char	*ft_itul(long long n)
{
	char		*p;
	long long	len;

	p = NULL;
	if (n == 0)
		return (zerocase(p));
	len = digit_count(n);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	return (line(len, p, n));
}
