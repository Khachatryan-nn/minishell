/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:33:29 by musimony          #+#    #+#             */
/*   Updated: 2023/09/08 15:19:36 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void static	while_loop(t_init *init, t_env *env, char *str);

void static	print_logo(void)
{
	write (1, "\033[38;5;60m\
╔═══════════════════════════════════════════════════════════════════════╗\n\
║░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░║\n\
║░░███╗░░░███╗██╗███╗░░░██╗██╗███████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░░░║\n\
║░░████╗░████║██║████╗░░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░░░║\n\
║░░██╔████╔██║██║██╔██╗░██║██║███████╗███████║█████╗░░██║░░░░░██║░░░░░░░║\n\
║░░██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝░░██║░░░░░██║░░░░░░░║\n\
║░░██║░╚═╝░██║██║██║░╚████║██║███████║██║░░██║███████╗███████╗███████╗░░║\n\
║░░╚═╝░░░░░╚═╝╚═╝╚═╝░░╚═══╝╚═╝╚══════╝╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝░░║\n\
║░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░║\n\
╚═══════════════════════════════════════════════════════════════════════╝\n\
\033[0m", 2215);
}

void	init_in(t_init *root)
{
	root->hdoc = 0;
	root->redir = 0;
	root->input = 0;
	root->fd_fail = 0;
	root->hd = NULL;
	root->lex = NULL;
	root->path = NULL;
	root->pars = NULL;
	root->temp = NULL;
	root->last_hdoc = -42;
	root->exit_status = 0;
}

void	leaks_check(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_env	*env;
	t_init	init;

	env = NULL;
	str = NULL;
	init.flag = 1;
	init_in(&init);
	env = env_init(envp, env);
	rl_catch_signals = 0;
	if (ac == 1 && av)
	{
		print_logo();
		init_hd(&init.hd);
		while_loop(&init, env, str);
	}
	return (0);
}

void static	while_loop(t_init *init, t_env *env, char *str)
{
	while (1)
	{
		save_backup(init);
		call_signals(1);
		str = readline("minishell$ ");
		if (!str)
		{
			ft_dprintf(2, "exit\n");
			exit (g_exit_status_);
		}
		if (!ft_onlyspaces(str))
		{
			lex(&str, init);
			if (init->pars)
			{
				init->exit_status = check_ast(init, init->pars, env);
				handle_dollar(init->exit_status, env);
				destroy_init(init);
				init->hd->i = 0;
			}
		}
		add_history(str);
		free(str);
	}
}

// command not found -> 127
// syntax || parsing error -> 258
// empty () -> 1
// unknown flag || parameter -> 1
// maximum exit value is 0->255, example: exit 256 -> 256 - 256 = 0, exit 300 -> 300 - 256 = 44
// exit "20"1 is the same, as exit "201" and exit 201
