/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:17:48 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/06 16:36:28 by musimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_list *str, char *ptr)
{
	t_list	*env;
	t_list	*env1;
	char	*text;
	char	*text1;

	text = NULL;
	text1 = NULL;
	text = ptr;
	env = NULL;
	env1 = NULL;
	while (*text == ' ' && *text)
		text++;
	while (*text != ' ' && *text)
		text++;
	while (*text == ' ' && *text)
		text++;
	if (chdir(text) == 0)
		ft_cd_continue(str, env, env1, text1);
	else if (text)
		ft_cd_home(str, env);
	else
		perror("minishell");
}

void	ft_cd_continue(t_list *str, t_list *env, t_list *env1, char *text1)
{
	env = str;
	while (env)
	{
		if (ft_strcmp(env->ptr, "PWD") == 0)
		{
			text1 = ft_strdup(env->value);
			free(env->value);
			env->value = ft_strjoin("=", ft_strdup(getcwd(NULL, 0)), 0);
			break ;
		}
		env = env->next;
	}
	env1 = str;
	ft_cd_continue2(env1, env, text1);
}

void	ft_cd_continue2(t_list *env1, t_list *env, char *text1)
{
	while (env1)
	{
		if (ft_strcmp(env1->ptr, "OLDPWD") == 0)
		{
			ft_cd_continue3(env1, env, text1);
			break ;
		}
		env1 = env1->next;
	}
}

void	ft_cd_continue3(t_list *env1, t_list *env, char *text1)
{
	if (env1->flag == 0)
		env1->flag = 1;
	if (env->unset == 0)
	{
		free(env1->ptr);
		env1->ptr = ft_strdup("OLDPWD");
		free(env1->value);
		env1->value = ft_strdup("=");
		env->unset = 1;
	}
	else
	{
		free(env1->ptr);
		env1->ptr = ft_strdup("OLDPWD");
		free(env1->value);
		env1->value = ft_strdup(text1);
	}
}

void	ft_cd_home(t_list *str, t_list *env)
{
	env = str;
	while (env)
	{
		if (ft_strcmp("HOME", env->ptr) == 0)
		{
			if (env->unset == 0)
			{
				printf("minishell$ cd: HOME not set\n");
				break ;
			}
			else
			{
				chdir(env->value + 1);
				break ;
			}
		}
		env = env->next;
	}
}
