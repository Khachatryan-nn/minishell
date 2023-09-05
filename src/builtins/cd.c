/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:17:48 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 23:53:57 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mshell_cd_helper(char *str, t_env *my_env);
void	mshell_cd(char **matrix, t_env *my_env);

void	mshell_cd(char **matrix, t_env *my_env)
{
	t_env	*tmp;
	char	*str;

	str = NULL;
	pwd_init(my_env);
	if (!matrix)
		return ;
	if (!matrix[1])
	{
		tmp = my_env;
		while (ft_strcmp(tmp->key, "HOME") != 0 && tmp->flag != 1)
			tmp = tmp->next;
		chdir(tmp->data);
		str = getcwd(NULL, 0);
		free(tmp->data);
		tmp->data = ft_strdup(str);
		free(str);
	}
	else if (chdir(matrix[1]) != 0)
	{
		ft_dprintf(2, "Minishell: cd: no such file or directory: %s\n", \
		matrix[1]);
		return ;
	}
	mshell_cd_helper(str, my_env);
}

void	mshell_cd_helper(char *str, t_env *my_env)
{
	t_env	*tmp;

	tmp = my_env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->pwd);
			str = getcwd(NULL, 0);
			if (str == NULL)
				builtins_error("cd", NULL);
			else
			{
				free(tmp->data);
				tmp->data = ft_strdup(str);
				tmp->pwd = ft_strdup(str);
			}
			if (!str)
				tmp->pwd = ft_strjoin(tmp->pwd, "/..", -1);
			free(str);
			break ;
		}
		tmp = tmp->next;
	}
}
