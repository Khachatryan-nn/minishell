/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:28:58 by musimony          #+#    #+#             */
/*   Updated: 2023/09/04 23:26:43 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*ptr;

	ptr = ft_lstlast(*lst);
	if (!ptr)
		*lst = new;
	else
	{
		ptr->next = new;
		ptr->next->prev = ptr;
	}
}
