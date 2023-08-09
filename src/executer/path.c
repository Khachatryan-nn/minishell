/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:56:36 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/27 13:27:32 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char static	*find_cmdpath(char *cmd, char **path);
void		find_path(t_init *init, t_list *env);
char		*check_cmd(char *cmd, char **path);

void	find_path(t_init *init, t_list *env)
{
	t_list	*env1;

	env1 = env; 
	while (env1)
	{
		if (ft_strcmp(env1->ptr, "PATH") == 0)
			break ;
		env1 = env1->next;
	}
	init->path = ft_split(env1->value, ':');
}


char static	*find_cmdpath(char *cmd, char **path)
{
	char	*cmdpath;
	int		i;

	i = -1;
	cmdpath = NULL;
	while (path[++i])
	{
		cmdpath = ft_strjoin(path[i], "/", 0);
		cmdpath = ft_strjoin(cmdpath, cmd, 1);
		if (access(cmdpath, X_OK) == -1)
			free (cmdpath);
		else
			return (cmdpath);
	}
	return (cmd);
}

char	*check_cmd(char *cmd, char **path)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (access(cmd, X_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
		{
			dprintf(2, "minishell: %s: No such file or directory\n", cmd);
			return (cmd_path);
		}
		cmd_path = find_cmdpath(cmd, path);
		if (!cmd_path)
		{
			dprintf(2, "minishell: %s: command not found\n", cmd);
			return (cmd_path);
		}
	}
	return (cmd_path);
}
