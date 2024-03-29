/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_strcts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:37:09 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/28 14:38:05 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lstsize_wcard(t_wcard *lst);
t_wcard	*lstadd_wcard(char *string);
t_wcard	*lstlast_wcard(t_wcard *lst);
void	lstclear_wcard(t_wcard **lst);
void	lstback_wcard(t_wcard **pars, t_wcard *new);

t_wcard	*lstadd_wcard(char *string)
{
	t_wcard		*tmp;

	tmp = (t_wcard *)malloc(sizeof(t_wcard));
	if (!tmp)
		return (NULL);
	tmp->file = ft_strdup(string);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void	lstback_wcard(t_wcard **pars, t_wcard *new)
{
	t_wcard	*tmp;

	tmp = lstlast_wcard(*pars);
	if (!tmp)
		*pars = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

void	lstclear_wcard(t_wcard **lst)
{
	t_wcard	*ptr;

	ptr = NULL;
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		ptr = (*lst)->next;
		free ((*lst)->file);
		free (*lst);
		(*lst) = ptr;
	}
	ptr = NULL;
}

t_wcard	*lstlast_wcard(t_wcard *lst)
{
	t_wcard	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	lstsize_wcard(t_wcard *lst)
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
