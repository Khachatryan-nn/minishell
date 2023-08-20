/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:34:10 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/21 00:58:17 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_prepair(t_init *init, t_parser *pars, t_list *env);

static int	child_left(t_init *init, t_parser *pars, t_list *env, int *pipes)
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
		exit(status);
	}
	return (pid); // Use call_cmd to execute the command
}

static int	child_right(t_init *init, t_parser *pars, t_list *env, int *pipes)
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
	pid = fork();
	
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