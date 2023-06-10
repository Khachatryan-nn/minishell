/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:58:16 by musimony          #+#    #+#             */
/*   Updated: 2023/01/29 19:08:26 by musimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s_len;
	size_t	d_len;

	i = 0;
	s_len = ft_strlen(src);
	if (!dest && size == 0)
		return (s_len);
	d_len = ft_strlen(dest);
	if (size < d_len + 1)
		return (size + s_len);
	if (size > d_len + 1)
	{
		while (src[i] != '\0' && d_len + 1 + i < size)
		{
			dest[d_len + i] = src[i];
			i++;
		}
	}
	dest[d_len + i] = '\0';
	return (s_len + d_len);
}
