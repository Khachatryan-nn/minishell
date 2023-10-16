/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:49:39 by tikhacha          #+#    #+#             */
/*   Updated: 2023/10/16 17:03:17 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_out(t_init *init, t_tok *stack);
int	open_in(t_init *init, t_tok *stack);
int	open_hd(t_tok *stack);

int	open_out(t_init *init, t_tok *stack)
{
	int	fd;

	fd = -42;
	if (stack->type == WR_APPEND)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 00655);
	else if (stack->type == WR_TRUNC)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 00655);
	if (fd == -1 && !init->fd_fail)
	{
		init->fd_fail = 1;
		ft_dprintf(2, "minishell: %s: No such file or directory\n", \
									stack->right->cmd);
	}
	return (fd);
}

int	open_hd(t_tok *stack)
{
	int	fd;

	fd = -42;
	fd = open(stack->hdoc_fname, O_RDWR, 0655);
	if (fd < 0)
		perror("minishell");
	return (fd);
}

int	open_in(t_init *init, t_tok *stack)
{
	int	fd;

	fd = -42;
	fd = open(stack->right->cmd, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", \
									stack->right->cmd);
		init->fd_fail = 1;
	}
	return (fd);
}
