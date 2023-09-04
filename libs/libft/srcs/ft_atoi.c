/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:09:33 by musimony          #+#    #+#             */
/*   Updated: 2023/09/04 14:51:48 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

long long	ft_atoi(const char *str)
{
	long long	i;
	long long	j;
	long long	k;

	i = 0;
	j = 1;
	k = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		k *= 10;
		k = k + (str[i] - '0');
		i++;
	}
	return (j * k);
}
