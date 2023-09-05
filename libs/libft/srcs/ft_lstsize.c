/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:16:04 by musimony          #+#    #+#             */
/*   Updated: 2023/09/04 23:27:29 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_lst *lst)
{
	int		i;
	t_lst	*str;

	i = 0;
	str = NULL;
	str = lst;
	while (str)
	{
		i++;
		(str) = (str)->next;
	}
	return (i);
}
