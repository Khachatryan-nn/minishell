/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:33:29 by musimony          #+#    #+#             */
/*   Updated: 2023/06/10 14:43:28 by musimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	int main(int ac, char **av, char **env1)
	{
		(void)av;
		char *str;
		t_list *env;

		env = NULL;
		ft_create_env(env1, &env);
		if (ac == 1)
		{
			while(1)
			{
				str = readline("minishall>: ");
				if (ft_strcmp(str, "env") == 0)
					ft_env(env);
				if (ft_strcmp(str, "pwd") == 0)
					ft_pwd(env);
				if (ft_strcmp(str, "cd ..") == 0)
					ft_cd(env, "..");
			}
		}
	}
