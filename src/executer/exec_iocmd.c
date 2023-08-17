/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/18 00:17:24 by tikhacha         ###   ########.fr       */
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
	int	pid;
	int status;

	stdin_backup = 0;
	status = 0;
	stdin_backup = dup(STDIN_FILENO);
	if (pipe(fd) < 0)
	{
		perror("minishell");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	else if (pid == 0)
	{
		close(fd[0]); //close the read end
		ft_putstr_fd(stack->right->cmd, fd[1]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close (fd[1]); //close the write end
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			close(fd[0]);
			perror("minishell");
			return (1);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && !WEXITSTATUS(status))
		{
			if (ft_strcmp(stack->left->cmd, "(NULL)"))
				init->exit_status = to_execute(stack->left, env, init, 0);
		}
		if (dup2(stdin_backup, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close (stdin_backup);
	}
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
