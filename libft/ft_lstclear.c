/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:34:27 by musimony          #+#    #+#             */
/*   Updated: 2023/01/29 17:38:31 by musimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst || !del)
		return ;
	tmp = *lst;
	tmp2 = *lst;
	while (tmp)
	{
		tmp2 = tmp2->next;
		del(tmp->content);
		free(tmp);
		tmp = tmp2;
	}
	*lst = 0;
}
