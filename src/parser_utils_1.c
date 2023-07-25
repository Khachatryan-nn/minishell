/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:42:42 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 00:09:52 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*lstnew_pars(char *content, t_type type, int prec, int flag);
void		lstback_pars(t_parser **lst, t_parser *new);
void		lstclear_pars(t_parser **lst);
t_parser	*lstlast_pars(t_parser *lst);
int			lstsize_pars(t_parser *lst);

t_parser	*lstnew_pars(char *content, t_type type, int prec, int flag)
{
	t_parser	*elt;

	elt = (t_parser *)malloc(sizeof(t_parser));
	if (!elt)
		return (NULL);
	elt->cmd = content;
	elt->type = type;
	elt->prc = prec;
	elt->is_cmd = flag;
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

void	lstback_pars(t_parser **lst, t_parser *new)
{
	t_parser	*ptr;

	ptr = lstlast_pars(*lst);
	if (!ptr)
		*lst = new;
	else
	{
		ptr->next = new;
		new->prev = ptr;
	}
}

void	lstclear_pars(t_parser **lst)
{
	t_parser	*ptr;

	ptr = NULL;
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		ptr = (*lst)->next;
		free ((*lst)->cmd);
		free (*lst);
		(*lst) = ptr;
	}
	ptr = NULL;
}

int	lstsize_pars(t_parser *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		(lst) = (lst)->next;
	}
	return (i);
}
