/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:17:48 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/19 01:19:07 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mshell_cd_helper(char *str, t_env *my_env);
void	mshell_cd(char **arr, t_env *my_env);
int		check_home(t_env *env);

void	mshell_cd(char **arr, t_env *my_env)
{
	char	*str;

	str = NULL;
	pwd_init(my_env);
	if (!arr)
		return ;
	if (!arr[1])
	{
		if (check_home(my_env))
			return ;
	}
	else if (chdir(arr[1]) != 0)
	{
		ft_dprintf(2, "minishell: cd: no such file or directory: %s\n", arr[1]);
		g_exit_status_ = -42;
		return ;
	}
	mshell_cd_helper(str, my_env);
}

int	check_home(t_env *env)
{
	t_env	*tmp;
	char	*str;

	str = NULL;
	tmp = env;
	while (ft_strcmp(tmp->key, "HOME"))
		tmp = tmp->next;
	if (!ft_strcmp(tmp->key, "HOME") && tmp->flag == 1)
	{
		ft_dprintf(2, "minishell: cd: HOME not set\n");
		g_exit_status_ = -42;
		return (1);
	}
	chdir(tmp->data);
	str = getcwd(NULL, 0);
	free(tmp->data);
	tmp->data = ft_strdup(str);
	free(str);
	return (0);
}

void	mshell_cd_helper(char *str, t_env *my_env)
{
	t_env	*tmp;

	tmp = my_env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			str = getcwd(NULL, 0);
			if (str == NULL)
			{
				builtins_error("cd", NULL);
				tmp->pwd = ft_strjoin(tmp->pwd, "/..", 1);
				free(tmp->data);
				tmp->data = ft_strdup(tmp->pwd);
				break ;
			}
			free(tmp->data);
			free(tmp->pwd);
			tmp->data = ft_strdup(str);
			tmp->pwd = str;
		}
		tmp = tmp->next;
	}
}
