/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:42:05 by musimony          #+#    #+#             */
/*   Updated: 2023/07/21 00:40:58 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str1, char *str2, int len)
{
	int		i;

	i = 0;
	if (len == 0)
	{
		while (str1[i] == str2[i])
			i++;
		if (str1[i] || str2[i])
			return (NULL);
		else
			return (str1);
	}
	else
	{
		while (str1[i] == str2[i] && i < len)
			i++;
		if (str1[i] != '\0' && str2[i] != '\0')
			return (NULL);
		else
			return (str1);		
	}

	// int		i;
	// char		*ptr;
	// char		*ptr1;

	// if (!*str2)
	// 	return ((char *)str1);
	// while (len-- && *str1)
	// {
	// 	if (*str1 == *str2)
	// 	{
	// 		i = len;
	// 		ptr = (char *)str1 + 1;
	// 		ptr1 = (char *)str2 + 1;
	// 		while (i-- && *ptr && *ptr1 && *ptr1 == *ptr)
	// 		{
	// 			++ptr1;
	// 			++ptr;
	// 		}
	// 		if (*ptr1 == '\0')
	// 			return ((char *)str1);
	// 	}
	// 	++str1;
	// }
	// return (NULL);
}
