/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:07:40 by musimony          #+#    #+#             */
/*   Updated: 2023/07/23 19:32:23 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin(char *s1, char *s2, int mode)
{
	char	*ptr;
	int	len_s1;
	int	len_s2;

	// if (!s1 && !s2)
	// 	return (ft_strdup(""));
	// if (s1 && !s2)
	// 	return (ft_strdup(s1));
	// if (!s1 && s2)
	// 	return (ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	k = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++k])
		new[i + k] = s2[k];
	new[len] = '\0';
	if (mode)
	{
		free(s1);
		s1 = 0;
	}
	return (new);
}
