/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_branch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:10:18 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 22:51:14 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	right_branch(t_init *in, t_tok *s, t_env *env, int status);
int	left_branch(t_init *in, t_tok *s, t_env *env, int status);

int	right_branch(t_init *in, t_tok *s, t_env *env, int status)
{
	int	pid;

	if (ch_reds(in, s, 1) && s->right->sub && check_type(s->right->type) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			s->err_code = check_ast(in, s->right, env);
			exit (s->err_code);
		}
		if (wait(&status) < 0)
		{
			perror("minishell");
			return (1);
		}
		s->err_code = status / 256;
	}
	else
		s->err_code = check_ast(in, s->right, env);
	return (s->err_code);
}

int	left_branch(t_init *in, t_tok *s, t_env *env, int status)
{
	int	pid;

	if (ch_reds(in, s, 1) && s->left->sub && check_type(s->left->type) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			s->err_code = check_ast(in, s->left, env);
			exit(s->err_code);
		}
		if (wait(&status) < 0)
		{
			perror("minishell");
			return (1);
		}
		if (WIFSIGNALED(status))
			s->err_code = WTERMSIG(status);
		else
			s->err_code = status / 256;
	}
	else
		s->err_code = check_ast(in, s->left, env);
	return (s->err_code);
}
