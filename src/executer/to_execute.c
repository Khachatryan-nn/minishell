/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:50:24 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/13 22:53:43 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd, char **matrix, char **env, t_tok *stack);
int	to_execute(t_init *init, t_tok *pars, t_env *env);
int	call_cmd(t_init *init, t_tok *stack, t_env *env);

int	to_execute(t_init *init, t_tok *stack, t_env *env)
{
	int	status;

	status = check_built(stack, env);
	if (g_exit_status_ == -42)
		return (stack->err_code);
	if (status == 1)
	{
		status = call_cmd(init, stack, env);
	}
	else if (status == -1)
		return (1);
	else
		if (io_backup(stack->stdin_backup, stack->stdout_backup))
			return (1);
	return (status);
}

int	exec_cmd(char *cmd, char **matrix, char **env, t_tok *stack)
{
	pid_t	pid;
	int		child_exit;

	child_exit = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	else if (pid == 0)
	{
		if (io_dup2(stack->_stdin_, stack->_stdout_))
			exit (EXIT_FAILURE);
		if (execve(cmd, matrix, env) == -1 && \
			execve(matrix[0], matrix, env) == -1)
		{
			perror("minishell");
			exit (EXIT_FAILURE);
		}
		exit (EXIT_SUCCESS);
	}
	waitpid(pid, &child_exit, 0);
	return (child_exit / 256);
}

int	call_cmd(t_init *init, t_tok *stack, t_env *env)
{
	char	**cmd_matrix;
	char	*cmd_path;
	char	**env_mtrx;
	int		exit_code;

	if (init->flag)
	{
		find_path(init, env);
		init->flag = 0;
	}
	if (do_expand(stack, env) && stack->cmd[0] == '\0')
		return (0);
	env_mtrx = env_matrix(env);
	if (!env_mtrx)
		return (127);
	cmd_matrix = restore_cmd_line(stack, -1);
	if (!cmd_matrix)
		return (destroy_cmd(0, 0, env_mtrx) + 1);
	cmd_path = check_cmd(cmd_matrix[0], init->path);
	if (!cmd_path)
		return (destroy_cmd(0, cmd_matrix, env_mtrx) + 126);
	exit_code = exec_cmd(cmd_path, cmd_matrix, env_mtrx, stack);
	destroy_cmd(cmd_path, cmd_matrix, env_mtrx);
	return (exit_code);
}

// command not found			->	127
// syntax || rooting error		->	258
// empty ()						->	1
// unknown flag || parameter	->	1
