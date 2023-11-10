/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/10/20 00:17:05 by tikhacha         ###   ########.fr       */
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

	fd = open_out(init, stack);
	if (fd < 0)
		return (1);
	tmp = stack;
	while (tmp->left->type != WORD && check_type(tmp->left->type) != 1 && \
					is_wrd(tmp->left) < 2)
		tmp = tmp->left;
	tmp->left->_stdout_ = fd;
	tmp->left->stdout_backup = init->stdout_backup;
	if (check_type(stack->type) == 2 && stack->sub)
		stack->last_red = 1;
	if (stack->last_red != 1 || init->fd_fail || \
		(check_type(stack->left->type) == 2 && stack->left->sub))
		return (0);
	if (ft_strcmp(stack->left->cmd, "(NULL)") && !(stack->flag & (1 << 7)))
		stack->err_code = check_ast(init, tmp->left, env);
	return (stack->err_code);
}

int	io_heredoc(t_init *init, t_tok *stack, t_env *env)
{
	t_tok	*tmp;
	int		fd;

	fd = open_hd(stack);
	if (fd < 0)
		return (1);
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	tmp->left->stdin_backup = init->stdin_backup;
	tmp->left->_stdin_ = fd;
	if (check_type(stack->type) == 2 && stack->sub)
		stack->last_hdoc = 1;
	if (stack->last_hdoc != 1 || init->fd_fail || tmp->left->type == PIPE || \
			(check_type(stack->left->type) == 2 && stack->left->sub))
		return (0 + unlink(stack->hdoc_fname));
	if (ft_strcmp(stack->right->cmd, "(NULL)"))
		stack->err_code = execute_second_arg(init, stack, env);
	if (ft_strcmp(tmp->left->cmd, "(NULL)"))
		stack->err_code |= to_execute(init, tmp->left, env);
	return (stack->err_code + unlink(stack->hdoc_fname));
}

int	io_input(t_init *init, t_tok *stack, t_env *env)
{
	t_tok	*tmp;
	int		fd;

	if (init->fd_fail == 1)
		return (1);
	fd = open_in(init, stack);
	if (fd < 0)
		return (init->fd_fail = 1, 1);
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	tmp->left->stdin_backup = init->stdin_backup;
	tmp->left->_stdin_ = fd;
	if (check_type(stack->type) == 2 && stack->sub)
		stack->last_input = 1;
	if (stack->last_input != 1 || (check_type(stack->left->type) == 2 \
				&& stack->left->sub))
		return (0);
	if (ft_strcmp(stack->right->cmd, "(NULL)"))
		stack->err_code = execute_second_arg(init, stack, env);
	stack->err_code |= check_ast(init, tmp->left, env);
	init->fd_fail = 0;
	return (stack->err_code);
}

int	exec_iocmd(t_init *init, t_tok *stack, t_env *env)
{
	ch_reds(init, stack, 0);
	if (stack->left->left && check_type(stack->left->type) == 2)
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
