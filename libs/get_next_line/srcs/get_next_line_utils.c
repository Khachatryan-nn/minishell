/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:41:36 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 14:56:21 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		n;
	int		i;
	char	*p;

	if (!s1)
		gnl_strdup("");
	if (!s1 || !s2)
		return (NULL);
	i = -1;
	n = gnl_strlen(s1) + gnl_strlen(s2) + 1;
	p = (char *)malloc(sizeof(char) * n);
	if (!p)
		return (NULL);
	while (++i < n)
	{
		if (*s1)
			p[i] = *s1++;
		else if (*s2)
			p[i] = *s2++;
	}
	p[i - 1] = '\0';
	free (s1);
	return (p);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	l = gnl_strlen(s);
	if ((size_t)start > l)
		return (gnl_strdup(""));
	if (len > l)
		len = l;
	p = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!p)
		return (0);
	while (i < len)
	{
		p[i] = *(s + start + i);
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*gnl_strdup(const char *s1)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)malloc(sizeof(char) * (gnl_strlen((char *)s1) + 1));
	if (p == NULL)
		return (NULL);
	while (s1[i])
	{
		p[i] = (char) s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((char) c == *s)
			return ((char *)s);
		s++;
	}
	if ((char) c == *s)
		return ((char *)s);
	return (NULL);
}
