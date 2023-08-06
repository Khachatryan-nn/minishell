/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:07:04 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/06 00:39:19 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(char *cmd_path, char **cmd_matrix, char **path);
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
	int	pid;

	pid = 0;
	// printf("exit segfault\n");
	if (!pars)
	{
		init->exit_status = 258;
		return (pars->err_code);
	}
	if (pars->left == NULL && pars->right == NULL)
	{
		// if (pars->flag & (1 << 6))
		if (pars->subshell_code)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				if (!check_built(pars, env, init))
				{
					pars->err_code = call_cmd(pars, init, env);
					init->exit_status = pars->err_code;
				}
			}
			return (1);
		}
		else if (!check_built(pars, env, init))
		{
			pars->err_code = call_cmd(pars, init, env);
			init->exit_status = pars->err_code;
		}
	}
	// else if (pars->lpath && pars->rpath)
	// {
	// 	printf("io command found\n");
	// 	exec_iocmd(init, pars, env);
	// }
	// else if (pars->type == PIPE || pars->flag & (1 << 5))
	// {
	// 	printf("pipe found\n");
	// 	pipe_prepair(pars);
	// }
	if (pars->left != NULL && !(pars->left->flag & (1 << 3)))
	{
		// if (pars->left->flag & (1 << 6))
		if (pars->left->subshell_code)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				pars->err_code = check_ast(init, pars->left, env);
			}
			return (1);
		}
		else
			pars->err_code = check_ast(init, pars->left, env);
	}
	if (pars->right != NULL && andor_check(pars) && !(pars->right->flag & (1 << 3)))
	{
		// if (pars->right->subshell_code) 00100001 & 00100000
		if (pars->right->flag & (1 << 6))
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
				pars->err_code = check_ast(init, pars->right, env);
			return (1);
		}
		else
			pars->err_code = check_ast(init, pars->right, env);
	}
	return (0);
}

int	execute_cmd(char *cmd_path, char **cmd_matrix, char **path)
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
		if (execve(cmd_path, cmd_matrix, path) == -1 && \
			execve(cmd_matrix[0], cmd_matrix, path) == -1)
		{
			perror("minishell");
			exit (1);
		}
		exit (0);
	}
	else
	{
		wait (&childExitCode);
		return (childExitCode);
	}
}

int	call_cmd(t_parser *stack, t_init *init, t_list *env)
{
	char	*cmd;
	char	**cmd_matrix;
	char	*cmd_path;

	if (!init->path)
		find_path(init, env);
	cmd = restore_cmd_line(stack);
	if (!cmd)
		return (1);
	cmd_matrix = ft_split(cmd, ' ');
	if (!cmd_matrix)
		return (2);
	cmd_path = check_cmd(cmd_matrix[0], init->path);
	if (!cmd_path)
		return (127);
	return (error_code(execute_cmd(cmd_path, cmd_matrix, init->path)));
}

// command not found			->	127
// syntax || parsing error		->	258
// empty ()						->	1
// unknown flag || parameter	->	1

// maximum exit value is 0->255, example: exit 256 -> 256 - 256 = 0, exit 300 -> 300 - 256 = 44
// exit "20"1 is the same, as exit "201" and exit 201
