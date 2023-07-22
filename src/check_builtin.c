/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:47:37 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/22 22:48:42 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built(char *str, t_list *env)
{
	if (ft_strcmp(str, "env") == 0)
	{
		ft_env(env);
		return (1);
	}
	if (ft_strnstr(str, "pwd", 3) == 0)
	{
		ft_pwd(env);
		return (1);
	}
	else if (ft_strnstr(str, "export", 6) == 0)
	{
		if (ft_strcmp(str, "export") == 0)
			ft_export(env);
		else
			ft_export_change(str, env);
		return (1);
	}
	else if (ft_strnstr(str, "unset", 5) == 0)
	{
		ft_unset(str, env);
		return (1);
	}
	else if (ft_strnstr(str, "cd", 2) == 0)
	{
		ft_cd(env, str);
		return (1);
	}
	return (0);
}
