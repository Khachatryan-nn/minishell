/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:07:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/23 20:40:19 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_lstadd_back_3(t_lexargs **lst, t_lexargs *new);
int			ft_isspace(char *line, int i, int j);
void		ft_lstclear_3(t_lexargs **lst);
t_lexargs	*ft_lstlast_3(t_lexargs *lst);
t_lexargs	*ft_lstnew_3(char *content, t_type type);

t_lexargs	*ft_lstnew_3(char *content, t_type type)
{
	t_lexargs	*elt;

	elt = (t_lexargs *)malloc(sizeof(t_lexargs));
	if (!elt)
		return (NULL);
	elt->cmd = content;
	elt->type = type;
	elt->next = NULL;
	elt->prev = NULL;
	return (elt);
}

t_lexargs	*ft_lstlast_3(t_lexargs *lst)
{
	t_lexargs	*ptr;

	ptr = lst;
	if (ptr == NULL)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_back_3(t_lexargs **lst, t_lexargs *new)
{
	t_lexargs	*ptr;

	ptr = ft_lstlast_3(*lst);
	if (!ptr)
		*lst = new;
	else
	{
		ptr->next = new;
		new->prev = ptr;
	}
}

void	ft_lstclear_3(t_lexargs **lst)
{
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		free ((*lst)->cmd);
		(*lst) = (*lst)->next;
	}
}

//Checks if there only spaces from i -> j.\
//If there are only spaces returns 1.
int	ft_isspace(char *line, int i, int j)
{
	while (i < j && line[i])
	{
		if (line[i] != ' ' && line[i] != '	')
			return (0);
		i++;
	}
	return (1);
}
