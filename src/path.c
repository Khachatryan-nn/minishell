/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:56:36 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/07 17:03:15 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	find_path(t_cmd *cmd, t_list *env);
int		check_cmd(t_cmd *cmd, t_list *env);
int		checker(t_cmd *cmd);

//Function to find and create matrix of cmd PATHs
void	find_path(t_cmd *cmd, t_list *env)
{
	t_list *env1;

	env1 = env;
	while (env1)
	{
		if (ft_strcmp(env1->ptr, "PATH") == 0)
			break;
		env1 = env1->next;
	}
		cmd->path = ft_split(env1->value, ':');
}

int	checker(t_cmd *cmd)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	i = -1;
	while (cmd->path[++i])
	{
		temp = ft_strjoin("/", cmd->cmd_args[0]);
		cmd_path = ft_strjoin(cmd->path[i], temp);
		free(temp);
		temp = 0;
		if (access(cmd_path, X_OK) == -1)
		{
			cmd->cmd_path = cmd_path;
			return (1);
		}
		free(cmd_path);
		cmd_path = 0;
	}
	return (0);
}

//Function to check if there are existing cmd like that
int	check_cmd(t_cmd *cmd, t_list *env)
{
	int	i;

	i = 0;
	while (*cmd->cmd_line == ' ')
		cmd->cmd_line++;
	cmd->cmd_args = ft_split(cmd->cmd_line, ' ');
	if(check_built(cmd->cmd_line, env))
			return(1);
	if (access(cmd->cmd_args[0], X_OK) == -1)
	{
		if (ft_strchr(cmd->cmd_args[0], '/') != NULL)
		{
			write (2, "Error: Unknown command.\n", 24);
			return (1);
		}
		else if (!checker(cmd))
		{
			write (2, "Error: Unknown command.\n", 24);
			return (1);
		}
	}
	return (0);
}