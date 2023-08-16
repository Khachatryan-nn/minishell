/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:42:42 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/16 23:48:12 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*lstnew_pars(char *content, t_type type, int prec, int flag);
void		lstback(t_parser **lst, t_parser *new);
void		lstclear(t_parser **lst);
t_parser	*lstlast(t_parser *lst);
int			lstsize(t_parser *lst);

t_parser	*lstnew_pars(char *content, t_type type, int prec, int flag)
{
	t_parser	*elt;

	elt = (t_parser *)malloc(sizeof(t_parser));
	if (!elt)
		return (NULL);
	elt->cmd = ft_strdup(content);
	elt->type = type;
	elt->prc = prec;
	elt->subshell_code = 0;
	elt->flag = flag;
	elt->err_code = 0;
	elt->lpath = NULL;
	elt->rpath = NULL;
	elt->next = NULL;
	elt->prev = NULL;
	elt->right = NULL;
	elt->left = NULL;
	return (elt);
}

t_parser	*lstlast(t_parser *lst)
{
	t_parser	*ptr;

	ptr = lst;
	if (!ptr)
		return (NULL);
	while (ptr && ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	lstback(t_parser **lst, t_parser *new)
{
	t_parser	*ptr;

	ptr = lstlast(*lst);
	if (!ptr)
		*lst = new;
	else
	{
		ptr->next = new;
		new->prev = ptr;
	}
}

void	lstclear(t_parser **lst)
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

int	lstsize(t_parser *lst)
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