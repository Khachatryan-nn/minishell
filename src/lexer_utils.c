/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:07:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/18 02:17:09 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_3(t_lexargs **lst, t_lexargs *new);
t_lexargs	*ft_lstlast_3(t_lexargs *lst);
t_lexargs	*ft_lstnew_3(char *content);
int	ft_isspace(char *line, int i, int j);

t_lexargs	*ft_lstnew_3(char *content)
{
	t_lexargs	*elt;

	elt = (t_lexargs *)malloc(sizeof(t_lexargs));
	if (!elt)
		return (NULL);
	elt->cmd = content;
	elt->next = NULL;
	return (elt);
}

t_lexargs	*ft_lstlast_3(t_lexargs *lst)
{
	t_lexargs *ptr;

	ptr = lst;
	if (!ptr)
		return (0);
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
		ptr->next = new;
}

//Checks if there only spaces from j -> i.\
//If there are only spaces returns 1.
int	ft_isspace(char *line, int i, int j)
{
	while(j < i && line[j])
	{
		if (line[j] != ' ' && line[j] != '	')
			return (0);
		j++;
	}
	return (1);
}
