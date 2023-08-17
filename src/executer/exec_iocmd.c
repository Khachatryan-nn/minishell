/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/17 17:55:04 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_iocmd(t_init *init, t_parser *stack, t_list *env);
int	io_out(t_init *init, t_parser *stack, t_list *env);
int io_heredoc(t_init *init, t_parser *stack, t_list *env);

int	io_out(t_init *init, t_parser *stack, t_list *env)
{
	int	fd;
	int	stdout_backup;

	fd = 0;
	if (stack->type == WRITE_APPEND)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 00755);
	else if (stack->type == WRITE_TRUNC)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
	{
		perror("minishell");
		close(fd);
		return (1);
	}
	if (fd != 0 && dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		close(fd);
		return (1);
	}
	if (ft_strcmp(stack->left->cmd, "(NULL)"))
		init->exit_status = to_execute(stack->left, env, init, 0);
	if (fd != 0 && dup2(stdout_backup, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		close(fd);
		return (1);
	}
	close(fd);
	close(stdout_backup);
	return (0);
}

int io_heredoc(t_init *init, t_parser *stack, t_list *env)
{
	int	fd[2];
	int	stdin_backup;

	stdin_backup = 0;
	if (pipe(fd) < 0)
	{
		perror("minishell");
		return (1);
	}
	stdin_backup = dup(STDIN_FILENO);
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		close(fd[0]);
		close(fd[1]);
		perror("minishell");
		return (1);
	}
	ft_putstr_fd(stack->right->cmd, fd[0]);
	if (ft_strcmp(stack->left->cmd, "(NULL)"))
		init->exit_status = to_execute(stack->left, env, init, 0);
	close (fd[0]);
	close (fd[1]);
	if (dup2(stdin_backup, STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (1);
	}
	close (stdin_backup);
	return (0);
}

int exec_iocmd(t_init *init, t_parser *stack, t_list *env)
{
	if (stack->type == WRITE_APPEND || stack->type == WRITE_TRUNC)
		return (io_out(init, stack, env));
	else if (stack->type == HEREDOC)
		return (io_heredoc(init, stack, env));
	// else if (stack->type == INPUT)
	// 	return (io_in(init, stack, env));
	return (1);
}
