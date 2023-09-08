/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:41:24 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/08 15:14:55 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_hdoc(int sig);
void	restore_prompt(int sig);
void	call_signals(int sig);
void	back_slash(int sig);
void	ctrl_c(int sig);

void	call_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		;
		// printf("exit\n");
		// exit(0);
	}
	if (sig == 4)
	{
		signal(SIGINT, sig_handler_hdoc);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	restore_prompt(int sig)
{
	g_exit_status_ = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

void	ctrl_c(int sig)
{
	g_exit_status_ = 130;
	write(1, "\n", 1);
	(void) sig;
}

void	back_slash(int sig)
{
	g_exit_status_ = 131;
	printf("Quit (core dumped)\n");
	(void) sig;
}

void	sig_handler_hdoc(int sig)
{
	(void) sig;
	g_exit_status_ = 130;
	write(1, "\n", 1);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}