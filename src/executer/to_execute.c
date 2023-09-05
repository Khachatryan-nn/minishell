/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:50:24 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/05 15:31:21 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_cmd(t_init *init, t_tok *stack, t_env *env);
int	to_execute(t_init *init, t_tok *pars, t_env *env);
int	exec_cmd(char *cmd, char **matrix, char **env, t_tok *stack);
// int	subsh_execute(t_init *init, t_tok *stack, t_env *env, int pid);

// int	subsh_execute(t_init *init, t_tok *stack, t_env *env, int pid)
// {
// 	int	status;

// 	status = 1;
// 	if (pid < 0)
// 		return (127);
// 	else if (pid == 0)
// 	{
// 		status = check_built(stack, env);
// 		if (status == 1)
// 			status = call_cmd(init, stack, env);
// 		else if (status == -1)
// 			exit (1);
// 		else
// 			if (io_backup(stack->stdin_backup, stack->stdout_backup))
// 				exit (1);
// 		exit (status);
// 	}
// 	if (wait(&status) < 0)
// 	{
// 		perror("wait");
// 		return (1);
// 	}
// 	return (status);
// }

int	to_execute(t_init *init, t_tok *stack, t_env *env)
{
	// int	pid;
	int	status;

	// if (stack->subshell_code)
	// {
	// 	pid = fork();
	// 	stack->err_code = subsh_execute(init, stack, env, pid);
	// 	return (stack->err_code);
	// }
	status = check_built(stack, env);
	if (status == 1)
		status = call_cmd(init, stack, env);
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
		perror("Minishell");
		return (1);
	}
	else if (pid == 0)
	{
		if (io_dup2(stack->_stdin_, stack->_stdout_))
			return (EXIT_FAILURE);
		if (execve(cmd, matrix, env) == -1 && \
			execve(matrix[0], matrix, env) == -1)
		{
			perror("Minishell");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &child_exit, 0);
		return (child_exit / 256);
	}
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
	do_expand(stack, env);
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
