/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:34:10 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/21 14:15:58 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_prepair(t_init *init, t_parser *pars, t_list *env);

static pid_t	child_left(t_init *init, t_parser *pars, t_list *env, int *pipes)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (dup2(pipes[1], STDOUT_FILENO) < 0)
			return (-1);
		close(pipes[0]);
		close(pipes[1]);
		status = check_ast(init, pars, env);
		exit (status);
	}
	return (pid);
}

static pid_t	child_right(t_init *init, t_parser *pars, t_list *env, int *pipes)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (dup2(pipes[0], STDIN_FILENO) < 0)
			return (-1);
		close(pipes[0]);
		close(pipes[1]);
		status = check_ast(init, pars, env);
		exit (status);
	}
	return (pid);
}

int	pipe_prepair(t_init *init, t_parser *pars, t_list *env)
{
	pid_t	pid_right;
	pid_t	pid_left;
	int		pipes[2];
	int		status;

	pars->left->flag |= (1 << 5);
	pars->right->flag |= (1 << 5);
	if (pipe(pipes) == -1)
	{
		pars->err_code = 1;
		perror("minishell");
		return (1);
	}
	pid_left = child_left(init, pars->left, env, pipes);
	if (pid_left < 0)
		return (1);
	pid_right = child_right(init, pars->right, env, pipes);
	if (pid_right < 0)
		return (1);
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (status);
}


//	xxxxxx1 -> command
//	xxxxx1x -> space
//	xxxx1xx -> executed or not (???)
//	xxx1xxx -> command for I/O
//	xx1xxxx -> arg for I/O
//	x1xxxxx -> pipe child
//	1xxxxxx -> subsh first cmd

//	1 << 0 -> 0000001 -> 1	| cmd						-> +++ USED
//	1 << 1 -> 0000010 -> 2	| space						-> +++ USED
//	1 << 2 -> 0000100 -> 4	| exec stat					-> --- unUSED
//	1 << 3 -> 0001000 -> 8	| I/O						-> +++ USED
//	1 << 4 -> 0010000 -> 16	| I/O arg					-> --- unUSED
//	1 << 5 -> 0100000 -> 32	| PIPE childs				-> ???
//	1 << 6 -> 1000000 -> 64 | SUBSH first command		-> +++ USED
//	1111111 -> 127