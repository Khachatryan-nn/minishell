/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:30:36 by musimony          #+#    #+#             */
/*   Updated: 2023/01/19 18:59:52 by musimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*ft_strchr(const char *str, int c)
// {
// 	unsigned char	ptr;
// 	int				i;

// 	i = 0;
// 	ptr = (unsigned char)c;
// 	while (str[i] && str[i] != ptr)
// 		i++;
// 	if (str[i] == ptr)
// 		return ((char *)str);
// 	else
// 		return (NULL);
// }
char	*ft_strchr(const char *str, int c)
{
	unsigned char	ptr;
	int				i;

	i = 0;
	ptr = (unsigned char)c;
	while (str[i]!= '\0' && str[i] != ptr)
		i++;
	if (str[i] == ptr)
		return ((char *)(str + i));
	else
		return (NULL);
}