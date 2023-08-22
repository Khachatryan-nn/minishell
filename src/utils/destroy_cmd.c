/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:07 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/22 13:05:40 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	destroy_cmd(char *cmd, char **cmd_matrix, char **env_matrix);

int	destroy_cmd(char *cmd, char **cmd_matrix, char **env_matrix)
{
	if (cmd)
		free (cmd);
	if (cmd_matrix)
		free_matrix(cmd_matrix);
	if (env_matrix)
		free_matrix(env_matrix);
	return (1);
}
