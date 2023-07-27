/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:17:48 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/22 22:52:11 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_list *str, char *ptr)
{
	t_list *env;
	t_list *env1;
	t_list *start;
	char	*text;
	char	*text1;

	(void)str;
	text = NULL;
	text1 = NULL;
	text = ptr;
	env = NULL;
	env1 = NULL;
	start = NULL;
 	while (*text == ' ' && *text)
		text++;
	while (*text != ' ' && *text)
		text++;
	while (*text == ' ' && *text)
		text++;
	if (chdir(text) == 0)
	{
		env = str;
		while (env)
		{
			if (ft_strcmp(env->ptr, "PWD") == 0)
			{
				text1 = ft_strdup(env->value);
				env->value = ft_strjoin("=", getcwd(NULL, 0), 0);
				env1 = str;
				while(env1)
					{
						if (ft_strcmp(env1->ptr, "OLDPWD") == 0)
							{
								if (env->flag == 1 && env->type == 1)
								{
									env1->value = ft_strdup(text1);
									printf("askjsabdcjkdsncksd\n");
								}
								else
								{
									env1->value = ft_strdup("=");
									env->flag = 1;
								}
								break;
							}
						env1 = env1->next;
					}
				}
			env = env->next;
			}
		}
	else
		perror("minishell");

}