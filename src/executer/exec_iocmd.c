/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:48:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/30 01:43:12 by tikhacha         ###   ########.fr       */
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
	if (init->redir == 0)
		stack->red = 1;
	init->redir--;
	if (stack->type == WRITE_APPEND)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 00655);
	else if (stack->type == WRITE_TRUNC)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 00655);
	if (stack->red != 1)
		return (1);
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

//int io_heredoc(t_init *init, t_parser *stack, t_list *env)
//{
//	int			stdin_backup;
//	t_parser	*temp;
//	int			pid;
//	int			status;
//	char		*res;

//	if (pipe(stack->pipes) < 0)
//	{
//		perror("minishell");
//		return (EXIT_FAILURE);
//	}
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("minishell");
//		return (EXIT_FAILURE + close_pipes(stack->pipes));
//	}
//	else if (pid == 0)
//	{
//		close(stack->pipes[0]);
//		res = heredoc_input(stack->right->cmd);
//		if (dup2(stack->pipes[1], STDOUT_FILENO) < 0)
//		{
//			perror("minishell");
//			exit(EXIT_FAILURE + close_pipes(stack->pipes));
//		}
//		write(STDOUT_FILENO, res, ft_strlen(res));
//		exit(EXIT_SUCCESS + _close_(stack->pipes[1]));
//	}
//	else
//	{
//		waitpid(pid, &status, 0);
//		if (status == EXIT_FAILURE)
//			return (1);
//		close(stack->pipes[1]);
//		stdin_backup = dup(STDIN_FILENO);
//		if (dup2(stack->pipes[0], STDIN_FILENO) < 0)
//		{
//			perror("minishell");
//			return (EXIT_FAILURE + _close_(stdin_backup) + close_pipes(stack->pipes));
//		}
//		temp = stack;
//		while (temp->left->type != WORD)
//			temp = temp->left;
//		if (ft_strcmp(temp->left->cmd, "(NULL)"))
//			init->exit_status = check_ast(init, temp->left, env);
//		if (dup2(stdin_backup, STDIN_FILENO) < 0)
//		{
//			perror("minishell");
//			return (1);
//		}
//		return (0 + _close2_(stdin_backup, stack->pipes[0]));
//	}
//	return (EXIT_FAILURE);
//}

int io_heredoc(t_init *init, t_parser *stack, t_list *env)
{
	int			stdin_backup;
	char		*res;
	int			fd;
	t_parser	*tmp;

	--init->hdoc;
	if (init->hdoc == 0)
		stack->last_hdoc = 1;
	if (stack->last_hdoc != 1)
		res = handle_heredoc_input(stack->right->cmd);
	else
	{
		res = handle_heredoc_input(stack->right->cmd);
		if (!res)
			return (1);
		fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0655);
		if (fd < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		stdin_backup = dup(STDIN_FILENO);
		if (stdin_backup < 0)
		{
			perror("minshell");
			return (EXIT_FAILURE);
		}
		write(fd, res, ft_strlen(res));
		close(fd);
		fd = open(".heredoc", O_RDWR, 0655);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("minishell");
			unlink(".heredoc");
			return (EXIT_FAILURE + _close2_(fd, stdin_backup));
		}
		close(fd);
		tmp = stack;
		while (tmp->left->type != WORD)
			tmp = tmp->left;
		if (ft_strcmp(tmp->left->cmd, "(NULL)"))
			init->exit_status = check_ast(init, tmp->left, env);
		if (dup2(stdin_backup, STDIN_FILENO) < 0)
		{
			perror("minishell");
			unlink(".heredoc");
			return (EXIT_FAILURE + _close2_(fd, stdin_backup));
		}
		close(stdin_backup);
		unlink(".heredoc");
	}
	free(res);
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
