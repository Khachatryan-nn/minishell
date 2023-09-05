/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:57:27 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 23:04:06 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_main(char *str, t_env *env, t_init init)
{
	if (!str)
	{
		printf("exit\n");
		while (env)
		{
			free(env->ptr);
			free(env->value);
			env = env->next;
		}
		free(str);
		exit(0);
	}
	else if (!ft_onlyspaces(str))
	{
		lex(str, &init);
		check_ast(&init, init.pars, env);
	}
}
