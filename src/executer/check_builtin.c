/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:06:56 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/30 01:34:44 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built(t_parser *stack, t_list *env, t_init *init)
{
	char	**cmd_matrix;

	cmd_matrix = restore_cmd_line(stack, -1);
	if (ft_strcmp(init->lex->cmd, "exit") == 0)
		ft_exit(env, init);
	 if (ft_strcmp(cmd_matrix[0], "env") == 0)
	{
		ft_env (env);
		return (1);
	}
	else if (ft_strnstr(cmd_matrix[0], "pwd", 3) == 0)
	{
		ft_pwd (env);
		return (1);
	}
	else if (ft_strnstr(cmd_matrix[0], "export", 6) == 0)
	{
		printf ("input: %s\n", cmd_matrix[0]);
		if (ft_strcmp(cmd_matrix[0], "export") == 0)
			ft_export (env);
		else
			ft_export_change (cmd_matrix[0], env, init);
		return (1);
	}
	else if (ft_strnstr(cmd_matrix[0], "unset", 5) == 0)
	{
		ft_unset(cmd_matrix[0], env, init);
		return (1);
	}
	else if (ft_strnstr(cmd_matrix[0], "cd", 2) == 0) 
	{
		ft_cd (env, cmd_matrix);
		return (1);
	}
	else if (ft_strnstr(cmd_matrix[0], "echo", 4) == 0)
	{
		ft_echo(env, init);
		return (1);
	}
	return (0);
}
