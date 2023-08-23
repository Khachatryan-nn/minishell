/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/23 19:00:55 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_iocmd(t_init *init, t_parser *stack, t_list *env);
int io_heredoc(t_init *init, t_parser *stack, t_list *env);
int	io_input(t_init *init, t_parser *stack, t_list *env);
int	io_out(t_init *init, t_parser *stack, t_list *env);

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
	while (stack->left->type != WORD)
		stack = stack->left;
	if (ft_strcmp(stack->left->cmd, "(NULL)"))
		init->exit_status = check_ast(init, stack->left, env);
	else if (ZSH)
		init->exit_status = to_execute(lstnew_pars("cat", WORD, 0, 0), env, init, 0);
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
	int			stdin_backup;
	t_parser	*temp;

	stdin_backup = dup(STDIN_FILENO);
	if (dup2(stack->pipes[0], STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (1 + _close_(stdin_backup) + close_pipes(stack->pipes));
	}
	temp = stack;
	while (temp->left->type != WORD)
		temp = temp->left;
	if (ft_strcmp(temp->left->cmd, "(NULL)"))
		init->exit_status = check_ast(init, temp->left, env);
	if (dup2(stdin_backup, STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (1);
	}
	close(stdin_backup);
	close_pipes(stack->pipes);
	return (0);
}

int	io_input(t_init *init, t_parser *stack, t_list *env)
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

int exec_iocmd(t_init *init, t_parser *stack, t_list *env)
{
	if (stack->type == WRITE_APPEND || stack->type == WRITE_TRUNC)
		return (io_out(init, stack, env));
	else if (stack->type == HEREDOC)
		return (io_heredoc(init, stack, env));
	 else if (stack->type == INPUT)
	 	return (io_input(init, stack, env));
	return (1);
}
