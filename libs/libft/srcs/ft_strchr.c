/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:30:36 by musimony          #+#    #+#             */
/*   Updated: 2023/08/16 02:07:05 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *str, int c)
{
	unsigned char	key;
	int				i;

	i = 0;
	if (!str)
		return (NULL);
	key = (unsigned char) c;
	while (str[i] != '\0' && str[i] != key)
		i++;
	if (str[i] == key)
		return ((char *) str + i);
	else
		return (NULL);
}