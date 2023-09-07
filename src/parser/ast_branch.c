/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:42:12 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 23:19:39 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*tree_end(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp);
t_tok	*tree_ops(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp);
t_tok	*tree_otp(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp);
t_tok	*ast_branch(t_tok *tok);

t_tok	*ast_branch(t_tok *tok)
{
	t_tok	*tmp;

	tmp = (t_tok *)malloc(sizeof(t_tok));
	if (!tmp)
		return (NULL);
	tmp->cmd = ft_strdup(tok->cmd);
	tmp->hdoc_fname = ft_strdup(tok->hdoc_fname);
	tmp->prc = tok->prc;
	tmp->flag = tok->flag;
	tmp->type = tok->type;
	tmp->last_red = tok->last_red;
	tmp->last_hdoc = tok->last_hdoc;
	tmp->last_input = tok->last_input;
	tmp->err_code = 0;
	tmp->sub = 0;
	tmp->fd = -42;
	tmp->_stdin_ = -42;
	tmp->_stdout_ = -42;
	tmp->stdin_backup = -42;
	tmp->stdout_backup = -42;
	tmp->prev = NULL;
	tmp->next = NULL;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

t_tok	*tree_end(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp)
{
	new = ast_branch(tmp);
	pop(stack);
	new->right = most_prev(abstract_syntax_tree(init, stack));
	if (!new)
		return (NULL);
	return (new);
}

t_tok	*tree_ops(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp)
{
	new = ast_branch(tmp);
	if (tmp->sub)
		new->sub = 1;
	pop(stack);
	new->right = most_prev(abstract_syntax_tree(init, stack));
	new->left = most_prev(abstract_syntax_tree(init, stack));
	if (new && check_type(new->type) == 2)
	{
		if (new->left)
			new->left->flag += _REDIR_;
		if (new->right)
			new->right->flag += _REDIR_;
	}
	return (new);
}

t_tok	*tree_otp(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp)
{
	while (tmp && tmp->cmd && (tmp->flag & 1) == 0)
	{
		push(stack, &init->temp);
		tmp = lstlast(*stack);
	}
	if (tmp && tmp->cmd && (tmp->flag & 1) == 1)
	{
		new = ast_branch(tmp);
		if (tmp->sub)
			new->sub = 1;
		pop(stack);
		while (init && init->temp)
			push(&init->temp, &new);
		return (new);
	}
	return (NULL);
}
