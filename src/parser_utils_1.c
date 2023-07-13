/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:42:42 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/14 00:49:03 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexargs	*lstnew_pars(char *content, t_type type)
{
	t_lexargs	*elt;

	elt = (t_lexargs *)malloc(sizeof(t_lexargs));
	if (!elt)
		return (NULL);
	elt->cmd = content;
	elt->type = type;
	elt->next = NULL;
	return (elt);
}

t_lexargs	*lstlast_pars(t_lexargs *lst)
{
	t_lexargs	*ptr;

	ptr = lst;
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	lstadd_back_pars(t_lexargs **lst, t_lexargs *new)
{
	t_lexargs	*ptr;

	ptr = lstlast_pars(*lst);
	if (!ptr)
		*lst = new;
	else
		ptr->next = new;
}

void	lstclear_pars(t_lexargs **lst)
{
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		free ((*lst)->cmd);
		(*lst) = (*lst)->next;
	}
}
