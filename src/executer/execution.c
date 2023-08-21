/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:07:04 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/22 01:32:52 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_path, char **cmd_matrix, char **env_mtrx, t_list *env);
int	check_ast(t_init *init, t_parser *pars, t_list *env);
int	call_cmd(t_parser *stack, t_init *init, t_list *env);
int	andor_check(t_parser *stack);

int	andor_check(t_parser *stack)
{
	if (stack->type == XAND && stack->left && stack->left->err_code != 0)
	{
		stack->err_code = stack->left->err_code;
		return (0);
	}
	else if (stack->type == XOR && stack->left && stack->left->err_code == 0)
	{
		stack->err_code = stack->left->err_code;
		return (0);
	}
	else
		return (1);
}

int	check_ast(t_init *init, t_parser *pars, t_list *env)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	if (!pars)
	{
		pars->err_code = 258;
		return (pars->err_code);
	}
	if (pars->left == NULL && pars->right == NULL)
	{
		pars->err_code = to_execute(pars, env, init, status);
		return (pars->err_code);
	}
	if (pars->left && pars->right && check_type(pars->type) == 2)
	{
		if (pars->left->left)
			check_ast(init, pars->left, env);
		pars->err_code = exec_iocmd(init, pars, env);
	}
	else if (pars->left && pars->right && pars->type == PIPE)
	{
		pars->err_code = pipe_prepair(init, pars, env);
	}
	if (pars->left != NULL && !(pars->left->flag & (_REDIR_)) && !(pars->left->flag & _PIPES_))
	{
		if (pars->left->subshell_code)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				pars->err_code = check_ast(init, pars->left, env);
				exit(pars->err_code);
			}
			else
			{
				if (wait(&status) < 0)
				{
					perror("wait");
					return (1);
				}
				exit_env(status, env);
				return (status);
			}
		}
		else
			pars->err_code = check_ast(init, pars->left, env);
	}
	if (pars->right != NULL && andor_check(pars) && !(pars->right->flag & (_REDIR_)) && !(pars->right->flag & _PIPES_))
	{
		if (pars->right->subshell_code)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				pars->err_code = check_ast(init, pars->right, env);
				exit(pars->err_code);
			}
			else
				wait(NULL);
			return (1);
		}
		else
			pars->err_code = check_ast(init, pars->right, env);
	}
	return (0);
}

int	exec_cmd(char *cmd_path, char **cmd_matrix, char **env_mtrx, t_list *env)
{
	pid_t	pid;
	int		childExitCode;

	childExitCode = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmd_matrix, env_mtrx) == -1 && \
			execve(cmd_matrix[0], cmd_matrix, env_mtrx) == -1)
		{
			perror("minishell");
			exit (1);
		}
		exit (0);
	}
	else
	{
		waitpid(pid, &childExitCode, 0);
		exit_env(childExitCode / 256, env);
		return (childExitCode / 256);
	}
}

int	call_cmd(t_parser *stack, t_init *init, t_list *env)
{
	char	**cmd_matrix;
	char	*cmd_path;
	char	**env_mtrx;
	int		exit_code;

	if (!init->path)
		find_path(init, env);
	env_mtrx = env_matrix(env);
	if (!env_mtrx)
	{
		free_matrix(env_mtrx);
		return (1);
	}
	cmd_matrix = restore_cmd_line(stack);
	if (!cmd_matrix)
	{
		free_matrix(env_mtrx);
		return (2);
	}
	cmd_path = check_cmd(cmd_matrix[0], init->path);
	if (!cmd_path)
	{
		free_matrix(cmd_matrix);
		free_matrix(env_mtrx);
		return (127);
	}
	exit_code = exec_cmd(cmd_path, cmd_matrix, env_mtrx, env);
	free(cmd_path);
	free_matrix(cmd_matrix);
	free_matrix(env_mtrx);
	return (exit_code);
}

// command not found			->	127
// syntax || parsing error		->	258
// empty ()						->	1
// unknown flag || parameter	->	1

// maximum exit value is 0->255, example: exit 256 -> 256 - 256 = 0, exit 300 -> 300 - 256 = 44
// exit "20"1 is the same, as exit "201" and exit 201