/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:06:56 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/08 15:40:19 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **matrix, t_tok	*stack);
int	check_built(t_tok *stack, t_env *env);
int	execute_builtin(t_tok *stack, t_env *env, char **matrix);

int	check_built(t_tok *stack, t_env *env)
{
	char	**cmd_matrix;
	int		status;

	do_expand(stack, env);
	cmd_matrix = restore_cmd_line(stack, -1);
	if (!cmd_matrix || !cmd_matrix[0])
		return (1);
	status = is_builtin(cmd_matrix, stack);
	if (!status)
		status = execute_builtin(stack, env, cmd_matrix);
	free_matrix(cmd_matrix);
	return (status);
}

int	execute_builtin(t_tok *stack, t_env *env, char **matrix)
{
	if (ft_strcmp(stack->cmd, "exit") == 0)
		return (mshell_exit(stack, matrix, env, NULL));
	else if (ft_strcmp(matrix[0], "env") == 0)
		mshell_env (env);
	else if (ft_strnstr(matrix[0], "pwd", 3) == 0)
		mshell_pwd (matrix[0], env);
	else if (ft_strnstr(matrix[0], "export", 6) == 0)
		mshell_export(matrix, env);
	else if (ft_strnstr(matrix[0], "unset", 5) == 0)
		mshell_unset(matrix, env);
	else if (ft_strnstr(matrix[0], "cd", 2) == 0)
		mshell_cd(matrix, env);
	else if (ft_strnstr(matrix[0], "echo", 4) == 0)
		mshell_echo(matrix);
	else
		return (1);
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
			return (0);
	}
	return (1);
}
