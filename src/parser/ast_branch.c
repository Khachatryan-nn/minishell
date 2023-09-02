/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:42:12 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/02 12:42:31 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*ast_branch(t_tok *tok);

t_tok	*ast_branch(t_tok *tok)
{
	t_tok	*tmp;

	tmp = (t_tok *)malloc(sizeof(t_tok));
	if (!tmp)
		return (NULL);
	tmp->cmd = ft_strdup(tok->cmd);
	tmp->hdoc_fname = ft_strdup(tok->hdoc_fname);
	tmp->flag = tok->flag;
	tmp->prc = tok->prc;
	tmp->type = tok->type;
	tmp->err_code = 0;
	tmp->last_red = tok->last_red;
	tmp->last_hdoc = tok->last_hdoc;
	tmp->last_input = tok->last_input;
	tmp->subshell_code = 0;
	tmp->fd = -42;
	tmp->_stdin_ = -42;
	tmp->_stdout_ = -42;
	tmp->stdin_backup = -42;
	tmp->stdout_backup = -42;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}