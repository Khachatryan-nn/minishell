/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lasts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:18:48 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 22:24:48 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ch_reds(t_init *init, t_tok *stack, int mode);
void static	last_redir(t_init *init, t_tok *stack);
void static	last_input(t_init *init, t_tok *stack);
void static	last_hd(t_init *init, t_tok *stack);

int	ch_reds(t_init *init, t_tok *stack, int mode)
{
	if (mode == 1)
	{
		init->last_hdoc = -42;
		init->last_redir = -42;
		init->last_input = -42;
		return (1);
	}
	last_hd(init, stack);
	last_redir(init, stack);
	last_input(init, stack);
	return (1);
}

void static	last_hd(t_init *init, t_tok *stack)
{
	if (init->last_hdoc < 0)
		stack->last_hdoc = 1;
	init->last_hdoc = 1;
}

void static	last_redir(t_init *init, t_tok *stack)
{
	if (init->last_redir < 0)
		stack->last_red = 1;
	init->last_redir = 1;
}

void static	last_input(t_init *init, t_tok *stack)
{
	if (init->last_input < 0)
		stack->last_input = 1;
	init->last_input = 1;
}
