/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:42:05 by musimony          #+#    #+#             */
/*   Updated: 2023/07/18 22:12:40 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *str1, size_t len)
{
	size_t		i;
	char		*ptr;
	char		*ptr1;

	if (!*str1)
		return ((char *)str);
	while (len-- && *str)
	{
		if (*str == *str1)
		{
			i = len;
			ptr = (char *)str + 1;
			ptr1 = (char *)str1 + 1;
			while (i-- && *ptr && *ptr1 && *ptr1 == *ptr)
			{
				++ptr1;
				++ptr;
			}
			if (*ptr1 == '\0')
				return ((char *)str);
		}
		++str;
	}
	return (NULL);
}
