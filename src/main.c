/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:33:29 by musimony          #+#    #+#             */
/*   Updated: 2023/08/05 15:51:24 by musimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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

int	main(int ac, char**av, char** env1)
{

	char	*str;
	t_list	*env;
	t_init	init;

	init.lex = NULL;
	init.pars = NULL;
	init.temp = NULL;
	init.path = NULL;
	env = NULL;
	init.flag = 1;
			
	str = (char *)malloc(sizeof(char) * 1024);
	ft_create_env(env1, &env);
	rl_catch_signals = 0;
	if (ac == 1 && av)
	{
		print_logo();
		while (1)
		{
			ft_signal();
			str = readline("minishell$ ");
			if (!str)
			{
				printf("exit\n");
				while (env)
				{
					free(env->ptr);
					free(env->value);
					env = env->next;
				}
				free(str);			
				break;
			}
			else if (ft_strcmp(str, "exit") == 0)
			{
				while (env)
				{
					free(env->ptr);
					free(env->value);
					env = env->next;
				}
				free(str);
				return (127);
			}
			else if (!ft_onlyspaces(str))
			{
				lex(str, &init);
				check_ast(&init, init.pars, env);
			}
			// ft_check_main(str, env, init);
			add_history(str);
	}
	}
	return(0);
}


// command not found -> 127
// syntax || parsing error -> 258
// empty () -> 1
// unknown flag || parameter -> 1
// maximum exit value is 0->255, example: exit 256 -> 256 - 256 = 0, exit 300 -> 300 - 256 = 44
// exit "20"1 is the same, as exit "201" and exit 201
