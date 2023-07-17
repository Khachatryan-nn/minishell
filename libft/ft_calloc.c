/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 01:20:42 by musimony          #+#    #+#             */
/*   Updated: 2023/07/16 02:37:52 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(nitems * size);
	if (nitems == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	if (str == 0)
		return (0);
	while (i < nitems * size)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}
