/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:56:36 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/18 02:17:21 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to find and create matrix of cmd PATHs
void	find_path(t_cmd *cmd)
{
	(void) cmd;
}

//Function to check if there are existing cmd like that
//void	check_cmd(t_cmd *cmd)
//{
//	if (access(cmd->cmd_, X_OK) == -1)
//	{
//		if (ft_strchr(pipex->cmd_args[0], '/') != NULL)
//		{
//			write (2, "Error: Unknown command.\n", 24);
//			exit (1);
//		}
//		else if (!checker(pipex))
//		{
//			write (2, "Error: Unknown command.\n", 24);
//			exit (1);
//		}
//	}
//}
