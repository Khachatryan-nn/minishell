/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:42:05 by musimony          #+#    #+#             */
/*   Updated: 2023/09/04 14:51:25 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr( char *str, char *str1, int len)
{
	int		i;

	i = 0;
	if (len == 0)
	{
		while (str[i] == str1[i])
			i++;
		if (str[i] || str1[i])
			return (str);
		else
			return (NULL);
	}
	else
	{
		while (str[i] == str1[i] && i < len)
			i++;
		if (str[i] != '\0' || str1[i] != '\0')
			return (str);
		else
			return (NULL);
	}
}
