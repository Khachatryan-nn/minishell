/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:51:16 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/05 16:34:41 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **ptr);
void	destroy_init(t_init *init);
void	destroy_structure(t_tok *root);
int		_free3_(void *ptr1, void *ptr2, void *ptr3);

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
	init->pars = NULL;
	init->lex = NULL;
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
		free (root->hdoc_fname);
	free (root);
	root = NULL;
	return ;
}

int	_free3_(void *ptr1, void *ptr2, void *ptr3)
{
	if (ptr1)
		free (ptr1);
	if (ptr2)
		free (ptr2);
	if (ptr3)
		free (ptr3);
	return (0);
}
