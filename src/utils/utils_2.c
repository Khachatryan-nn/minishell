/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:54:43 by tikhacha          #+#    #+#             */
/*   Updated: 2023/10/16 18:14:46 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swaping(t_init *init, t_tok **cmd_l);
void	set_links(t_tok **tmp);

void	swaping(t_init *init, t_tok **cmd_l)
{
	init->lex = init->lex->next;
	init->lex->flag |= 1;
	pop_redir(*cmd_l);
}

void	set_links(t_tok **tmp)
{
	(*tmp)->next->prc = 0;
	(*tmp)->next->flag = 1;
	(*tmp)->next->prev = (*tmp)->prev;
	(*tmp)->prev->next = (*tmp)->next;
	(*tmp)->next = NULL;
	(*tmp)->prev = NULL;
	free((*tmp)->cmd);
	free(*tmp);
}
