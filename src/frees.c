/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:51:16 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/24 16:09:18 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	void	*ptr;

	if (!init)
		return ;
	//if (init->lex && init->lex->cmd)
	//	free(init->lex->cmd);
	while (init->lex)
	{
		ptr = init->lex->next;
		free (init->lex);
		init->lex = ptr;
	}
	while (init->pars)
	{
		ptr = init->pars->next;
		free (init->pars->cmd);
		free (init->pars);
		init->pars = ptr;
	}
	init->pars = NULL;
	init->lex = NULL;
	ptr = NULL;
}
