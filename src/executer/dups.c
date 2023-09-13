/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 08:52:58 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/13 22:36:33 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_backup(int stdin_backup, int stdout_backup);
int	io_dup2(int _stdin, int _stdout);

int	io_dup2(int _stdin, int _stdout)
{
	if (_stdin >= 0)
	{
		if (dup2(_stdin, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	if (_stdout >= 0)
	{
		if (dup2(_stdout, STDOUT_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	return (0);
}

int	io_backup(int stdin_backup, int stdout_backup)
{
	if (stdin_backup >= 0)
	{
		if (dup2(stdin_backup, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	if (stdout_backup >= 0)
	{
		if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
