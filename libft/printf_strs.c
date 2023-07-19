/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:14:34 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/18 22:36:44 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchr(char c)
{
	write (2, &c, 1);
	return (1);
}

int	ft_putstr(char *s, int t)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)", 0));
	while (s[i] != '\0')
		ft_putchr(s[i++]);
	if (t == 1)
	{
		free(s);
		s = 0;
	}
	return (i);
}
