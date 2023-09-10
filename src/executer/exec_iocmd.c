/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/11 01:09:30 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_iocmd(t_init *init, t_tok *stack, t_env *env);
int	io_heredoc(t_init *init, t_tok *stack, t_env *env);
int	io_input(t_init *init, t_tok *stack, t_env *env);
int	io_out(t_init *init, t_tok *stack, t_env *env);

int	io_out(t_init *init, t_tok *stack, t_env *env)
{
	int		fd;
	t_tok	*tmp;

	fd = -42;
	if (stack->type == WR_APPEND)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 00655);
	else if (stack->type == WR_TRUNC)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 00655);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	tmp->left->_stdout_ = fd;
	tmp->left->stdout_backup = init->stdout_backup;
	if (stack->last_red != 1 || init->fd_fail)
		return (0);
	if (ft_strcmp(stack->left->cmd, "(NULL)") && !(stack->flag & (1 << 7)))
		stack->err_code = check_ast(init, tmp->left, env);
	return (stack->err_code);
}

int	io_heredoc(t_init *init, t_tok *stack, t_env *env)
{
	t_tok	*tmp;
	int		fd;

	fd = open(stack->hdoc_fname, O_RDWR, 0655);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	tmp = stack;
	while (tmp->left->type != WORD && tmp->left->type != PIPE \
		&& !tmp->left->sub)
	{
		if (tmp->left->type == HEREDOC)
			unlink(tmp->left->hdoc_fname);
		tmp = tmp->left;
	}
	tmp->left->stdin_backup = init->stdin_backup;
	tmp->left->_stdin_ = fd;
	if (stack->last_hdoc != 1 || init->fd_fail || tmp->left->type == PIPE \
		|| tmp->left->sub)
		return (0 + unlink(stack->hdoc_fname));
	if (ft_strcmp(tmp->left->cmd, "(NULL)"))
		stack->err_code = check_ast(init, tmp->left, env);
	return (stack->err_code + unlink(stack->hdoc_fname));
}

int	io_input(t_init *init, t_tok *stack, t_env *env)
{
	t_tok	*tmp;
	int		fd;

	fd = open(stack->right->cmd, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		init->fd_fail = 1;
		return (EXIT_FAILURE);
	}
	if (init->fd_fail == 1)
		return (1);
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	tmp->left->stdin_backup = init->stdin_backup;
	tmp->left->_stdin_ = fd;
	if (stack->last_input != 1)
		return (0);
	stack->err_code = check_ast(init, tmp->left, env);
	init->fd_fail = 0;
	return (stack->err_code);
}

int	exec_iocmd(t_init *init, t_tok *stack, t_env *env)
{
	ch_reds(init, stack, 0);
	if (stack->left->left)
		stack->err_code = check_ast(init, stack->left, env);
	if (init->exit_status == EXIT_SUCCESS)
	{
		if (stack->type == WR_APPEND || stack->type == WR_TRUNC)
			return (io_out(init, stack, env));
		else if (stack->type == HEREDOC)
			return (io_heredoc(init, stack, env));
		else if (stack->type == INPUT)
			return (io_input(init, stack, env));
	}
	if (stack->hdoc_fname)
		unlink(stack->hdoc_fname);
	return (stack->err_code);
}
