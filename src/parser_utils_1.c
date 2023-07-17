/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:42:42 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/16 20:46:35 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		lstadd_back_pars(t_parser **lst, t_parser *new);
t_parser	*lstnew_pars(char *content, t_type type);
void		lstclear_pars(t_parser **lst);
t_parser	*lstlast_pars(t_parser *lst);

t_parser	*lstnew_pars(char *content, t_type type)
{
	t_parser	*elt;

	elt = (t_parser *)malloc(sizeof(t_parser));
	if (!elt)
		return (NULL);
	elt->cmd = content;
	elt->type = type;
	elt->next = NULL;
	elt->prev = NULL;
	elt->right = NULL;
	elt->left = NULL;
	return (elt);
}

t_parser	*lstlast_pars(t_parser *lst)
{
	t_parser	*ptr;

	ptr = lst;
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	lstadd_back_pars(t_parser **lst, t_parser *new)
{
	t_parser	*ptr;

	ptr = lstlast_pars(*lst);
	if (!ptr)
		*lst = new;
	else
	{
		ptr->next = new;
		ptr->next->prev = ptr;
	}
}

void	lstclear_pars(t_parser **lst)
{
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		free ((*lst)->cmd);
		(*lst) = (*lst)->next;
	}
}
