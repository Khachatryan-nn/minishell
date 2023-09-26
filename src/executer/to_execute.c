/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:50:24 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/21 22:10:13 by tikhacha         ###   ########.fr       */
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
	if (status == 1)
		status = call_cmd(init, stack, env);
	else
	{
		stack->err_code = 1;
		if (io_backup(stack->stdin_backup, stack->stdout_backup))
			return (1);
	}
	if (g_exit_status_ == 130)
		return (130);
	if (status == -1 || g_exit_status_ == -42)
		return (1);
	else if (g_exit_status_ == -100)
		return (stack->err_code);
	return (status);
}

void static	exec_error(t_tok *stack, char *cmd, int err_num)
{
	if (err_num == 13)
	{
		ft_dprintf(2, "minishell: %s: is a directory\n", cmd);
		stack->err_code = 125;
	}
	else
		ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
}

int	exec_cmd(char *cmd, char **matrix, char **env, t_tok *stack)
{
	pid_t	pid;
	int		child_exit;

	child_exit = 0;
	pid = fork();
	call_signals(2);
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	else if (pid == 0)
	{
		if (io_dup2(stack->_stdin_, stack->_stdout_))
			exit (EXIT_FAILURE);
		if (execve(cmd, matrix, env) == -1)
		{
			exec_error(stack, cmd, errno);
			exit (EXIT_FAILURE + stack->err_code);
		}
		exit (EXIT_SUCCESS);
	}
	waitpid(pid, &child_exit, 0);
	return (child_exit / 256);
}

int static	destroy_unsetcase(char *path, char **mtrx, char **env, t_tok *s)
{
	ft_dprintf(2, "minishell: %s: No such file or directory\n", s->cmd);
	destroy_cmd(path, mtrx, env);
	return (127);
}

int	call_cmd(t_init *init, t_tok *stack, t_env *env)
{
	char	**cmd_matrix;
	char	**env_mtrx;
	char	*cmd_path;
	int		exit_code;

	find_path(init, env);
	if (do_expand(stack, env) && stack->cmd[0] == '\0')
		return (0);
	//print_types(stack);
	env_mtrx = env_matrix(env);
	if (!env_mtrx)
		return (127);
	cmd_matrix = restore_cmd_line(stack, -1);
	if (!cmd_matrix)
		return (destroy_cmd(0, 0, env_mtrx) + 1);
	cmd_path = check_cmd(init, stack, cmd_matrix[0], init->path);
	if (init->flag == 2)
		return (destroy_unsetcase(cmd_path, cmd_matrix, env_mtrx, stack));
	if (!cmd_path)
		return (destroy_cmd(0, cmd_matrix, env_mtrx) + 126 + stack->err_code);
	exit_code = exec_cmd(cmd_path, cmd_matrix, env_mtrx, stack);
	destroy_cmd(cmd_path, cmd_matrix, env_mtrx);
	return (exit_code);
}
