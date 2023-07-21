/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:07:40 by musimony          #+#    #+#             */
/*   Updated: 2023/07/21 19:30:04 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		len;
	int		i;
	int		k;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
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
	return (new);
}
