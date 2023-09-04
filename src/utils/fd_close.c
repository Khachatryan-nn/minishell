/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 00:57:17 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 13:26:25 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_close_(int	fd);
int	close_pipes(int *fd);
int	_close2_(int fd1, int fd2);
int	_close3_(int fd1, int fd2, int fd3);

int	_close_(int	fd)
{
	if (close(fd) < 0)
	{
		perror("minishell");
		return (-10);
	}
	return (0);
}

int	_close2_(int fd1, int fd2)
{
	if (fd1 >= 0 && close(fd1) < 0)
	{
		perror("minishell");
		return (-10);
	}
	if (fd2 >= 0 && close(fd2) < 0)
	{
		perror("minishell");
		return (-10);
	}
	return (0);
}

int	_close3_(int fd1, int fd2, int fd3)
{
	if (close(fd1) < 0)
	{
		perror("minishell");
		return (-10);
	}
	if (close(fd2) < 0)
	{
		perror("minishell");
		return (-10);
	}
	if (close(fd3) < 0)
	{
		perror("minishell");
		return (-10);
	}
	return (0);
}

int	close_pipes(int *fd)
{
	close (fd[0]);
	close (fd[1]);
	return (0);
}
