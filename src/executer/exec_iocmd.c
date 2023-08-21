/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/21 18:04:07 by tikhacha         ###   ########.fr       */
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
			while (stack->left->type != WORD)
				stack = stack->left;
			if (ft_strcmp(stack->left->cmd, "(NULL)"))
				init->exit_status = to_execute(stack->left, env, init, 0);
		}
		close (fd[0]);
		if (dup2(stdin_backup, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close (stdin_backup);
	}
	return (0);
}

int	io_input(t_init *init, t_parser *stack, t_list *env)
{
	int		status;
	int		fd[2];
	int		file_fd;
	int		backup;
	char	*str;
	int		pid;

	backup = dup(STDIN_FILENO);
	if (pipe(fd) < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		close(fd[0]);
		close(fd[1]);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		file_fd = open(stack->right->cmd, O_RDONLY);
		if (file_fd < 0)
		{
			perror("minishell");
			close (fd[1]);
			exit(EXIT_FAILURE);
		}
		while (1)
		{
			str = get_next_line(file_fd);
			if (!str)
				break ;
			ft_putstr_fd(str, fd[1]);
		}
		close (fd[1]);
		close (file_fd);
		exit (EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			perror("minishell");
			close (fd[0]);
			return (EXIT_FAILURE);
		}
		waitpid(pid, &status, 0);
		while (stack->left->type != WORD)
			stack = stack->left;
		if (WIFEXITED(status) && !WEXITSTATUS(status))
			init->exit_status = to_execute(stack->left, env, init, 0);
		close (fd[0]);
		if (dup2(backup, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		close (backup);
	}
	return (0);
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
