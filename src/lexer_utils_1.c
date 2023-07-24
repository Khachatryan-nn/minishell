/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:07:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/24 16:06:42 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexargs	*lstnew_lex(char *content, t_type type, int prec);
void		lstback_lex(t_lexargs **lst, t_lexargs *new);
int			ft_isspace(char *line, int i, int j);
void		lstclear_lex(t_lexargs **lst);
t_lexargs	*lstlast_lex(t_lexargs *lst);

t_lexargs	*lstnew_lex(char *content, t_type type, int prec)
{
	t_lexargs	*elt;

	elt = (t_lexargs *)malloc(sizeof(t_lexargs));
	if (!elt)
		return (NULL);
	elt->cmd = content;
	elt->type = type;
	elt->prc = prec;
	elt->next = NULL;
	elt->prev = NULL;
	return (elt);
}

t_lexargs	*lstlast_lex(t_lexargs *lst)
{
	t_lexargs	*ptr;

	ptr = lst;
	if (ptr == NULL)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	lstback_lex(t_lexargs **lst, t_lexargs *new)
{
	t_lexargs	*ptr;

	ptr = lstlast_lex(*lst);
	if (!ptr)
		*lst = new;
	else
	{
		ptr->next = new;
		new->prev = ptr;
	}
}

void	lstclear_lex(t_lexargs **lst)
{
	t_lexargs	*ptr;

	ptr = NULL;
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		ptr = (*lst)->next;
		free ((*lst)->cmd);
		free(*lst);
		(*lst) = ptr;
	}
	ptr = NULL;
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