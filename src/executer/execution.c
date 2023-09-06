/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:07:04 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/05 22:49:30 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ast(t_init *init, t_tok *root, t_env *env);
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

int	check_ast(t_init *init, t_tok *root, t_env *env)
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
		root->err_code = to_execute(init, root, env);
		handle_dollar(root->err_code, env);
		return (root->err_code);
	}
	if (root->left && root->right && check_type(root->type) == 2)
	{
		check_lasts(init, root, 0);
		if (root->left->left)
			check_ast(init, root->left, env);
		if (init->exit_status == EXIT_SUCCESS)
			root->err_code = exec_iocmd(init, root, env);
		if (root->hdoc_fname)
			unlink(root->hdoc_fname);
	}
	else if (root->left && root->right && root->type == PIPE) // && stack->left->type != HEREDOC && stack->right->type != HEREDOC)
		root->err_code = pipe_prepair(init, root, env);
	if (root->left != NULL && !(root->left->flag & _REDIR_) && \
		!(root->left->flag & _PIPES_))
	{
		check_lasts(init, root, 1);
		if (root->left->subshell_code && check_type(root->left->type) == 1)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				root->err_code = check_ast(init, root->left, env);
				exit(root->err_code);
			}
			if (wait(&status) < 0)
			{
				perror("minishell");
				return (1);
			}
			if (WIFSIGNALED(status))
				root->err_code = WTERMSIG(status);
			else
				root->err_code = status;
		}
		else
			root->err_code = check_ast(init, root->left, env);
	}
	if (root->right != NULL && andor_check(root) && \
		!(root->right->flag & (_REDIR_)) && !(root->right->flag & _PIPES_))
	{
		check_lasts(init, root, 1);
		if (root->right->subshell_code && check_type(root->right->type) == 1)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				root->err_code = check_ast(init, root->right, env);
				exit (root->err_code);
			}
			if (wait(&status) < 0)
			{
				perror("minishell");
				return (1);
			}
			if (WIFSIGNALED(status))
				root->err_code = WTERMSIG(status);
			else
				root->err_code = status;
			//exit_env(status, env);
		}
		else
			root->err_code = check_ast(init, root->right, env);
	}
	return (0);
}
