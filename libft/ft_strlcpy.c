/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:02:23 by musimony          #+#    #+#             */
/*   Updated: 2023/07/16 02:37:52 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s_len;
	char	*ptr;

	ptr = (char *)src;
	i = 0;
	s_len = ft_strlen(ptr);
	if (!dest || !ptr)
		return (0);
	if (size != 0)
	{
		while (ptr[i] != '\0' && i < size - 1)
		{
			dest[i] = ptr[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (s_len);
}
