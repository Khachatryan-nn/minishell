/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:51:16 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 19:09:21 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_structure(t_parser *root);
void	destroy_init(t_init *init);
void	free_matrix(void **ptr);

void	free_matrix(void **ptr)
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

void	destroy_structure(t_parser *root)
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
	free (root);
	root = NULL;
	return ;
}
