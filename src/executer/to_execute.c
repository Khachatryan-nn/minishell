/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:50:24 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/03 00:50:04 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_execute(t_tok *pars, t_lst *env, t_init *init, int status);
int	subsh_execute(t_tok *pars, t_lst *env, t_init *init, int pid);

int	subsh_execute(t_tok *pars, t_lst *env, t_init *init, int pid)
{
	int	status;

	status = 0;
	if (pid == -1)
		return (127);
	else if (pid == 0)
	{
		if (check_built(pars, env, init))
			kill(pid, SIGKILL);
		else
		{
			pars->err_code = call_cmd(pars, init, env);
			init->exit_status = pars->err_code;
		}
	}
	else
	{
		if (wait(&status) < 0)
		{
			perror("wait");
			return (1);
		}
		return (status);
	}
	return (0);
}

int	to_execute(t_tok *pars, t_lst *env, t_init *init, int status)
{
	int	pid;

	if (pars->subshell_code)
	{
		pid = fork();
		return (subsh_execute(pars, env, init, pid));
	}
	else if (!check_built(pars, env, init))
	{
		pars->err_code = call_cmd(pars, init, env);
		init->exit_status = pars->err_code;
	}
	else
	{
		if (pars->stdin_backup > 0)
		{
			if (dup2(pars->stdin_backup, STDIN_FILENO) < 0)
			{
				perror("minishell");
				return (EXIT_FAILURE + close(pars->stdin_backup));
			}
			close(pars->stdin_backup);
		}
		if (pars->stdout_backup > 0)
		{
			if (dup2(pars->stdout_backup, STDOUT_FILENO) == -1)
			{
				perror("Minishell");
				return (1);
			}
			close(pars->stdout_backup);
		}		
	}
	return (status);
}
