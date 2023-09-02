/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:17:48 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/02 12:34:02 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_lst *str, char **ptr)
{
	t_lst	*env;
	t_lst	*env1;
	int		flag1;
	char	*text;
	char	*text1;

	text = NULL;
	text1 = NULL;
	text = ptr[0];
	env = NULL;
	env1 = NULL;
	flag1 = 0;
	while (*text == ' ' && *text)
		text++;
	while (*text != ' ' && *text)
		text++;
	while (*text == ' ' && *text)
		text++;
	if (*text == '\0')
	{
		env = str;
		while (env)
		{
			if (ft_strcmp("HOME", env->ptr) == 0)
				{
					chdir(env->value + 1);
					break;
				}
			env = env->next;
		}
	}
	else if (chdir(text) == 0)
	{
		env = str;
		while (env)
		{
			if (ft_strcmp(env->ptr, "PWD") == 0)
			{
				if (env->unset == 0)
					flag1 = 1;
				text1 = ft_strdup(env->value);
				free(env->value);
				env->value = ft_strjoin("=", ft_strdup(getcwd(NULL, 0)), 0);
				break;
			}
			env = env->next;
		}
		env1 = str;
		while (env1)
		{
			if (ft_strcmp(env1->ptr, "OLDPWD") == 0)
			{
				if (env1->flag == 0)
					env1->flag = 1;
				if (flag1 == 1)
				{
					free(env1->ptr);
					env1->ptr = ft_strdup("OLDPWD");
					free(env1->value);
					env1->value = ft_strdup("=");
					env->unset = 1;
					break;
				}
				else
					{
						free(env1->ptr);
						env1->ptr = ft_strdup("OLDPWD");
						free(env1->value);
						env1->value = ft_strdup(text1);
						break;
					}
			}
		env1 = env1->next;
		}
	}
	else
		perror("minishell$");
}
