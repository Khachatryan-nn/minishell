/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:51:16 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/16 23:27:16 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		_free3_(char *ptr1, char **ptr2, char **ptr3);
void	destroy_structure(t_tok *root);
void	destroy_init(t_init *init);
void	free_matrix(char **ptr);

void	free_matrix(char **ptr)
{
	int	i;

	i = -1;
	if (ptr == NULL)
		return ;
	while (ptr[++i] != NULL)
		free(ptr[i]);
	free (ptr);
	ptr = 0;
}

void	destroy_init(t_init *init)
{
	if (!init)
		return ;
	destroy_structure(init->lex);
	destroy_structure(init->pars);
	init->hdoc = 0;
	init->redir = 0;
	init->input = 0;
	init->fd_fail = 0;
	init->lex = NULL;
	if (init->path)
		free_matrix(init->path);
	init->path = NULL;
	init->pars = NULL;
	init->temp = NULL;
	init->last_hdoc = -42;
}

void	destroy_structure(t_tok *root)
{
	if (!root)
		return ;
	if (root->right)
		destroy_structure(root->right);
	if (root->left)
		destroy_structure(root->left);
	if (root->next)
		destroy_structure(root->next);
	if (root->cmd)
		free (root->cmd);
	if (root->type == HEREDOC && root->hdoc_fname)
	{
		unlink (root->hdoc_fname);
		free (root->hdoc_fname);
	}
	free (root);
	root = NULL;
	return ;
}

int	_free3_(char *ptr1, char **ptr2, char **ptr3)
{
	if (ptr1)
		free (ptr1);
	if (ptr2)
		free_matrix(ptr2);
	if (ptr3)
		free_matrix(ptr3);
	return (0);
}
