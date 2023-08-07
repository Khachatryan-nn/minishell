/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/01 19:10:40 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_iocmd(t_init *init, t_parser *stack, t_list *env);

int	exec_iocmd(t_init *init, t_parser *stack, t_list *env)
{
	(void) init;
	(void) stack;
	(void) env;
	return (0);
	// if (pipe(stack->pipes) == -1 || pipe(stack->left->pipes) == -1)
	// 	return (1);
	// if (stack->type == HEREDOC)
	// {
	// 	if (!stack->lpath)
	// 	{
	// 		write (1, )
	// 	}
	// }
}
