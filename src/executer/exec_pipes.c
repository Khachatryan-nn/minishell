/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:34:10 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/19 00:58:00 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_prepair(t_init *init, t_parser *pars, t_list *env);

static void	child_process(t_init *init, t_parser *pars, t_list *env, int *pipes)
{
	int	status;

	close(pipes[0]); // Close read end
	dup2(pipes[1], STDOUT_FILENO);
	status = check_ast(init, pars, env);
	close(pipes[1]);
	exit(status); // Use call_cmd to execute the command
}

static void	parent_process(t_init *init, t_parser *pars, t_list *env, int *pipes, int pid)
{
	int status;

	waitpid(pid, &status, 0);
	pars->err_code = WEXITSTATUS(status);
	close(pipes[1]); // Close write end
	if (!(pars->flag & (1 << 5))) // Assuming 5 represents pipe child flag
		close(pipes[0]); // Close read end
	else
		pars->pipes[0] = pipes[0];
	status = check_ast(init, pars, env);
}

int	pipe_prepair(t_init *init, t_parser *pars, t_list *env)
{
	int		pipes[2];
	pid_t	pid;

	pars->left->flag |= (1 << 5);
	pars->right->flag |= (1 << 5);

	if (pipe(pipes) == -1)
	{
		pars->err_code = 1;
		perror("minishell");
		return (1);
	}

	pid = fork();
	if (pid < 0)
	{
		pars->err_code = 1;
		close_pipes(pipes);
		perror("minishell");
		return (1);
	}
	else if (pid == 0)
		child_process(init, pars->left, env, pipes);
	else
	{
		parent_process(init, pars->right, env, pipes, pid);
		return (pars->err_code);
	}
	return (0);
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