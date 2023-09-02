/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:07:04 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/02 12:34:02 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd_path, char **cmd_matrix, char **env_mtrx, t_lst *env);
int	check_ast(t_init *init, t_tok *root, t_lst *env);
int	call_cmd(t_tok *stack, t_init *init, t_lst *env);
int	andor_check(t_tok *stack);

int	andor_check(t_tok *stack)
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

int	check_ast(t_init *init, t_tok *root, t_lst *env)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	if (!root)
	{
		root->err_code = 258;
		return (root->err_code);
	}
	if (root->left == NULL && root->right == NULL)
	{
		root->err_code = to_execute(root, env, init, status);
		//handle_dollar(root->err_code, env);
		return (root->err_code);
	}
	if (root->left && root->right && check_type(root->type) == 2)
	{
		check_lasts(init, root, 0);
		if (root->left->left)
			check_ast(init, root->left, env);
		root->err_code = exec_iocmd(init, root, env);
	}
	else if (root->left && root->right && root->type == PIPE)
		root->err_code = pipe_prepair(init, root, env);
	if (root->left != NULL && !(root->left->flag & _REDIR_) && !(root->left->flag & _PIPES_))
	{
		check_lasts(init, root, 1);
		if (root->left->subshell_code)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				root->err_code = check_ast(init, root->left, env);
				exit(root->err_code);
			}
			else
			{
				if (wait(&status) < 0)
				{
					perror("minishell");
					return (1);
				}
				//exit_env(status, env);
				return (status);
			}
		}
		else
			root->err_code = check_ast(init, root->left, env);
	}
	if (root->right != NULL && andor_check(root) && !(root->right->flag & (_REDIR_)) && !(root->right->flag & _PIPES_))
	{
		check_lasts(init, root, 1);
		if (root->right->subshell_code)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				root->err_code = check_ast(init, root->right, env);
				exit(root->err_code);
			}
			else
				wait(NULL);
			return (1);
		}
		else
			root->err_code = check_ast(init, root->right, env);
	}
	return (0);
}

int	exec_cmd(char *cmd_path, char **cmd_matrix, char **env_mtrx, t_lst *env)
{
	pid_t	pid;
	int		child_exit_code;

	child_exit_code = 0;
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
		waitpid(pid, &child_exit_code, 0);
		exit_env(child_exit_code / 256, env);
		return (child_exit_code / 256);
	}
}

int	call_cmd(t_tok *stack, t_init *init, t_lst *env)
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
	env_mtrx = env_matrix(env);
	if (!env_mtrx)
		return (127);
	cmd_matrix = restore_cmd_line(stack, -1);
	if (!cmd_matrix)
		return (destroy_cmd(0, 0, env_mtrx) + 1);
	cmd_path = check_cmd(cmd_matrix[0], init->path);
	if (!cmd_path)
		return (destroy_cmd(0, cmd_matrix, env_mtrx) + 126);
	exit_code = exec_cmd(cmd_path, cmd_matrix, env_mtrx, env);
	destroy_cmd(cmd_path, cmd_matrix, env_mtrx);
	return (exit_code);
}

// command not found			->	127
// syntax || rooting error		->	258
// empty ()						->	1
// unknown flag || parameter	->	1

// maximum exit value is 0->255, example: exit 256 -> 256 - 256 = 0, exit 300 -> 300 - 256 = 44
// exit "20"1 is the same, as exit "201" and exit 201