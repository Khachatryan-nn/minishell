/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:45:57 by musimony          #+#    #+#             */
/*   Updated: 2023/07/18 22:12:39 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getstart(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	ptr = (char *)s1;
	len = ft_strlen (ptr);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(s2, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_getend(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;
	char	*ptr1;

	ptr1 = (char *)s1;
	len = ft_strlen(ptr1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(s2, s1[len - 1 - i]) == 0)
			break ;
		i++;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *s2)
{
	int		start;
	int		end;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (ft_strdup(s1));
	start = ft_getstart(s1, s2);
	end = ft_getend(s1, s2);
	if (start >= end)
		return (ft_strdup(""));
	str = (char *)(malloc (sizeof(char) * (end - start + 1)));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
