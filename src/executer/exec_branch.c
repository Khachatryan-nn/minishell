/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_branch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:10:18 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/13 17:42:11 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		right_branch(t_init *in, t_tok *s, t_env *env, int status);
int		left_branch(t_init *in, t_tok *s, t_env *env, int status);
void	config_right_dups(t_tok *stack);
void	config_left_dups(t_tok *stack);

int	right_branch(t_init *in, t_tok *s, t_env *env, int status)
{
	int	pid;

	config_right_dups(s);
	if (ch_reds(in, s, 1) && s->right->sub && check_type(s->right->type) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			s->err_code = check_ast(in, s->right, env);
			exit (s->err_code);
		}
		if (wait(&status) < 0)
		{
			perror("minishell");
			return (1);
		}
		s->err_code = status / 256;
	}
	else
		s->err_code = check_ast(in, s->right, env);
	return (s->err_code);
}

int	left_branch(t_init *in, t_tok *s, t_env *env, int status)
{
	int	pid;

	config_left_dups(s);
	if (ch_reds(in, s, 1) && s->left->sub && check_type(s->left->type) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			s->err_code = check_ast(in, s->left, env);
			exit (s->err_code);
		}
		if (wait(&status) < 0)
		{
			perror("minishell");
			return (1);
		}
		if (WIFSIGNALED(status))
			s->err_code = WTERMSIG(status);
		else
			s->err_code = status / 256;
	}
	else
		s->err_code = check_ast(in, s->left, env);
	return (s->err_code);
}

void	config_right_dups(t_tok *stack)
{
	if (stack->type == END)
		return ;
	if (stack->stdin_backup != -42)
		stack->right->stdin_backup = stack->stdin_backup;
	if (stack->stdout_backup != -42)
		stack->right->stdout_backup = stack->stdout_backup;
	if (stack->_stdin_ != -42)
		stack->right->_stdin_ = stack->_stdin_;
	if (stack->_stdout_ != -42)
		stack->right->_stdout_ = stack->_stdout_;
	if (stack->fd != -42)
		stack->right->fd = stack->fd;
}

void	config_left_dups(t_tok *stack)
{
	if (stack->type == END)
		return ;
	if (stack->stdin_backup != -42)
		stack->left->stdin_backup = stack->stdin_backup;
	if (stack->stdout_backup != -42)
		stack->left->stdout_backup = stack->stdout_backup;
	if (stack->_stdin_ != -42)
		stack->left->_stdin_ = stack->_stdin_;
	if (stack->_stdout_ != -42)
		stack->left->_stdout_ = stack->_stdout_;
	if (stack->fd != -42)
		stack->right->fd = stack->fd;
}
