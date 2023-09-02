/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/02 12:58:34 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_iocmd(t_init *init, t_tok *stack, t_lst *env);
int io_heredoc(t_init *init, t_tok *stack, t_lst *env);
int	io_input(t_init *init, t_tok *stack, t_lst *env);
int	io_out(t_init *init, t_tok *stack, t_lst *env);

int	io_out(t_init *init, t_tok *stack, t_lst *env)
{
	int	fd;
	int	stdout_backup;

	fd = 0;
	init->redir--;
	if (stack->type == WR_APPEND)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 00655);
	else if (stack->type == WR_TRUNC)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 00655);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
	{
		perror("minishell");
		return (1 + _close_(fd));
	}
	if (fd != 0 && dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		return (1 + _close_(fd));
	}
	while (stack->left->type != WORD)
		stack = stack->left;
	if (ft_strcmp(stack->left->cmd, "(NULL)") && !(stack->flag & (1 << 7)))
		init->exit_status = check_ast(init, stack->left, env);
	else if (ZSH)
		init->exit_status = to_execute(lstnew_pars("cat", WORD, 0, 0), env, init, 0);
	if (fd != 0 && dup2(stdout_backup, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		return (1 + _close_(fd));
	}
	return (init->exit_status + _close2_(fd, stdout_backup));
}

int io_heredoc(t_init *init, t_tok *stack, t_lst *env)
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
	while (tmp->left->type != WORD)
	{
		if (tmp->left->type == HEREDOC)
			unlink(tmp->left->hdoc_fname);
		tmp = tmp->left;
	}
	if (init->redir == 1)
	{
		tmp->left->stdin_backup = init->stdin_backup;
		tmp->left->_stdin_ = fd;
		unlink(stack->hdoc_fname);
		return (1);
	}
	if (ft_strcmp(tmp->left->cmd, "(NULL)"))
	{
		tmp->left->stdin_backup = init->stdin_backup;
		tmp->left->_stdin_ = fd;
		init->exit_status = check_ast(init, tmp->left, env);
		unlink(stack->hdoc_fname);
	}
	return (0);
}


int	io_input(t_init *init, t_tok *stack, t_lst *env)
{
	int		file_fd;
	int		backup;

	backup = dup(STDIN_FILENO);
	if (backup < 0)
		perror("minishell");
	file_fd = open(stack->right->cmd, O_RDONLY);
	if (file_fd < 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE + _close_(backup));
	}
	if (dup2(file_fd, STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE + _close2_ (file_fd, backup));
	}
	while (stack->left->type != WORD)
		stack = stack->left;
	init->exit_status = to_execute(stack->left, env, init, 0);
	if (dup2(backup, STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	return (0 + _close2_(backup, file_fd));
}

int exec_iocmd(t_init *init, t_tok *stack, t_lst *env)
{
	if (stack->type == WR_APPEND || stack->type == WR_TRUNC)
		return (io_out(init, stack, env));
	else if (stack->type == HEREDOC)
		return (io_heredoc(init, stack, env));
	 else if (stack->type == INPUT)
	 	return (io_input(init, stack, env));
	return (1);
}
