/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:27:06 by musimony          #+#    #+#             */
/*   Updated: 2023/07/18 22:12:39 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1cpy;
	size_t	len;
	size_t	i;

	s1cpy = (char *)s1;
	if (!s1)
		return(NULL);
	len = ft_strlen(s1cpy);
	s1cpy = malloc((len + 1) * sizeof(char));
	i = 0;
	if (s1cpy == 0)
		return (0);
	while (i < len)
	{
		s1cpy[i] = s1[i];
		i++;
	}
	s1cpy[i] = '\0';
	return (s1cpy);
}
