/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:56:36 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 13:49:31 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char static	*find_cmdpath(char *cmd, char **path);
void		find_path(t_init *init, t_env *env);
char		*check_cmd(char *cmd, char **path);

void	find_path(t_init *init, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PATH") == 0)
		{
			if (temp->flag)
			{
				init->path = NULL;
				return ;
			}
			break ;
		}
		temp = temp->next;
	}
	init->path = ft_split(temp->data, ':');
}

char static	*find_cmdpath(char *cmd, char **path)
{
	char	*cmdpath;
	int		i;

	i = -1;
	cmdpath = NULL;
	if (cmd[0] == '\0')
		return (NULL);
	while (path && path[++i])
	{
		cmdpath = ft_strjoin(path[i], "/", 0);
		cmdpath = ft_strjoin(cmdpath, cmd, 1);
		if (access(cmdpath, X_OK | F_OK) == -1)
			free (cmdpath);
		else
			return (cmdpath);
	}
	return (NULL);
}

char	*check_cmd(char *cmd, char **path)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (access(cmd, X_OK | F_OK) == -1)
	{
		if ((ft_strchr(cmd, '/') && access(cmd, X_OK) == -1))
		{
			ft_dprintf(2, "minishell: %s: No such file or directory\n", cmd);
			return (cmd_path);
		}
		cmd_path = find_cmdpath(cmd, path);
		if (!cmd_path)
			ft_dprintf(2, "minishell: %s: command not found\n", cmd);
		return (cmd_path);
	}
	else if (!access(cmd, X_OK | F_OK))
		return (ft_strdup(cmd));
	else if (ft_strchr(cmd, '/'))
	{
		ft_dprintf(2, "minishell: %s: is a directory\n", cmd);
		return (cmd_path);
	}
	return (ft_strdup(cmd));
}
