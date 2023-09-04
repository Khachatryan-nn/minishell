/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:06:56 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 16:38:04 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **matrix, t_tok	*stack);
int	check_built(t_tok *stack, t_lst *env, t_init *init);
int	execute_builtin(t_init *init, t_tok *stack, t_lst *env, char **matrix);

int	check_built(t_tok *stack, t_lst *env, t_init *init)
{
	char	**cmd_matrix;
	int		status;

	cmd_matrix = restore_cmd_line(stack, -1);
	if (!cmd_matrix || !cmd_matrix[0])
		return (0);
	status = is_builtin(cmd_matrix, stack);
	if (status <= 0)
		return (status);
	status = execute_builtin(init, stack, env, cmd_matrix);
	free_matrix(cmd_matrix);
	return (status);
}

int	execute_builtin(t_init *init, t_tok *stack, t_lst *env, char **matrix)
{
	if (ft_strcmp(stack->cmd, "exit") == 0)
		ft_exit(env, init);
	else if (ft_strcmp(matrix[0], "env") == 0)
		ft_env (env);
	else if (ft_strnstr(matrix[0], "pwd", 3) == 0)
		ft_pwd (env);
	else if (ft_strnstr(matrix[0], "export", 6) == 0)
	{
		printf ("input: %s\n", matrix[0]);
		if (ft_strcmp(matrix[0], "export") == 0)
			ft_export (env);
		else
			ft_export_change (matrix[0], env, init);
	}
	else if (ft_strnstr(matrix[0], "unset", 5) == 0)
		ft_unset(matrix[0], env, init);
	else if (ft_strnstr(matrix[0], "cd", 2) == 0)
		ft_cd (env, matrix);
	else if (ft_strnstr(matrix[0], "echo", 4) == 0)
		ft_echo(env, init);
	else
		return (0);
	return (1);
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
