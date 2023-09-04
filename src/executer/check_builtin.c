/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:06:56 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 13:33:46 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **matrix, t_tok	*stack);
int	check_built(t_tok *stack, t_lst *env, t_init *init);

int	check_built(t_tok *stack, t_lst *env, t_init *init)
{
	char	**cmd_matrix;
	int		is_built;

	cmd_matrix = restore_cmd_line(stack, -1);
	is_built = is_builtin(cmd_matrix, stack);
	if (is_built <= 0)
		return (is_built);
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

int	is_builtin(char **matrix, t_tok	*stack)
{
	if (!ft_strcmp(matrix[0], _ENV_) || !ft_strcmp(matrix[0], _ECHO_) || \
		!ft_strcmp(matrix[0], _PWD_) || !ft_strcmp(matrix[0], _CD_) || \
		!ft_strcmp(matrix[0], _EXIT_) || !ft_strcmp(matrix[0], _EXPORT_) || \
		!ft_strcmp(matrix[0], _UNSET_))
	{
		if (io_dup2(stack->_stdin_, stack->_stdout_))
			return (-1);
		else
			return (1);
	}
	return (0);
}
