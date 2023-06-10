/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:27:06 by musimony          #+#    #+#             */
/*   Updated: 2023/01/29 19:05:03 by musimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*s1cpy;
	size_t	len;
	size_t	i;

	s1cpy = (char *)s1;
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
