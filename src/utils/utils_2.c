/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:54:43 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/26 17:57:16 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swaping(t_init *init, t_tok **cmd_l);

void	swaping(t_init *init, t_tok **cmd_l)
{
	init->lex = init->lex->next;
	init->lex->flag |= 1;
	pop_redir(*cmd_l);
}
