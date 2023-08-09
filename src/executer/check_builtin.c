/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:06:56 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/09 17:59:25 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built(t_parser *stack, t_list *env, t_init *init)
{
	char	*str;

	str = restore_cmd_line(stack);
	if (ft_strcmp(init->lex->cmd, "exit") == 0)
		ft_exit(env, init);
	 if (ft_strcmp(str, "env") == 0)
	{
		ft_env (env);
		return (1);
	}
	else if (ft_strnstr(str, "pwd", 3) == 0)
	{
		ft_pwd (env);
		return (1);
	}
	else if (ft_strnstr(str, "export", 6) == 0)
	{
		printf ("input: %s\n", str);
		if (ft_strcmp(str, "export") == 0)
			ft_export (env);
		else
			ft_export_change (str, env, init);
		return (1);
	}
	else if (ft_strnstr(str, "unset", 5) == 0)
	{
		ft_unset(str, env, init);
		return (1);
	}
	else if (ft_strnstr(str, "cd", 2) == 0)
	{
		ft_cd (env, str);
		return (1);
	}
	else if (ft_strnstr(str, "echo", 4) == 0)
	{
		ft_echo(env, init);
		return (1);
	}
	return (0);
}
