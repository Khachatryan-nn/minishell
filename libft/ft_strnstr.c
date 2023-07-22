/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:42:05 by musimony          #+#    #+#             */
/*   Updated: 2023/07/22 23:00:48 by tikhacha         ###   ########.fr       */
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
}
