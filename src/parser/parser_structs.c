/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:42:42 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/02 12:56:27 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*lstnew_pars(char *content, t_type type, int prec, int flag);
void		lstback(t_tok **lst, t_tok *new);
void		lstclear(t_tok **lst);
t_tok	*lstlast(t_tok *lst);
int			lstsize(t_tok *lst);

t_tok	*lstnew_pars(char *content, t_type type, int prec, int flag)
{
	t_tok		*elt;

	elt = (t_tok *)malloc(sizeof(t_tok));
	if (!elt)
		return (NULL);
	elt->prc = prec;
	elt->flag = flag;
	elt->type = type;
	elt->err_code = 0;
	elt->last_red = -1;
	elt->last_hdoc = 0;
	elt->last_input = -1;
	elt->subshell_code = 0;
	elt->fd = -42;
	elt->_stdin_ = -42;
	elt->_stdout_ = -42;
	elt->stdin_backup = -42;
	elt->stdout_backup = -42;
	elt->left = NULL;
	elt->next = NULL;
	elt->prev = NULL;
	elt->right = NULL;
	elt->hdoc_fname = NULL;
	elt->cmd = ft_strdup(content);
	return (elt);
}

t_tok	*lstlast(t_tok *lst)
{
	t_tok	*ptr;

	ptr = lst;
	if (!ptr)
		return (NULL);
	while (ptr && ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	lstback(t_tok **lst, t_tok *new)
{
	t_tok	*ptr;

	ptr = lstlast(*lst);
	if (!ptr)
		*lst = new;
	else
	{
		ptr->next = new;
		new->prev = ptr;
	}
}

void	lstclear(t_tok **lst)
{
	t_tok	*ptr;

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

int	lstsize(t_tok *lst)
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
