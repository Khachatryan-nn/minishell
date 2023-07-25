/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:42:05 by musimony          #+#    #+#             */
/*   Updated: 2023/07/25 22:30:58 by tikhacha         ###   ########.fr       */
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
			return(NULL);
		else
			return(str);
	}
	else
	{
		while (str[i] == str1[i] && i < len)
			i++;
		if (str[i]!= '\0' && str1[i] != '\0')
			return(str);
		else
			return(NULL);		
	}

	// int		i;
	// char		*ptr;
	// char		*ptr1;

	// if (!*str1)
	// 	return ((char *)str);
	// while (len-- && *str)
	// {
	// 	if (*str == *str1)
	// 	{
	// 		i = len;
	// 		ptr = (char *)str + 1;
	// 		ptr1 = (char *)str1 + 1;
	// 		while (i-- && *ptr && *ptr1 && *ptr1 == *ptr)
	// 		{
	// 			++ptr1;
	// 			++ptr;
	// 		}
	// 		if (*ptr1 == '\0')
	// 			return ((char *)str);
	// 	}
	// 	++str;
	// }
	// return (NULL);
}
