/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:33:29 by musimony          #+#    #+#             */
/*   Updated: 2023/07/21 00:53:22 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int ac, char **av, char **env1)
{
	char	*str;
	t_list	*env;
	t_init	init;

	init.lex = NULL;
	init.pars = NULL;
	env = NULL;
	ft_create_env(env1, &env);
	if (ac == 1 && av)
	{
		print_logo();
		while (1)
		{
			str = readline("minishell$ ");
			if (ft_strcmp(str, "") == 0)
				continue ;
			else if (ft_strcmp(str, "exit") == 0)
			{
				while (env)
				{
					free(env->ptr);
					free(env->value);
					env = env->next;
				}
				return (127);
			}
			else if (ft_strnstr(str, "cd", 2))
				ft_cd(env, ft_strchr(str, str[3]));
			else if (!ft_onlyspaces(str))
				lex(str, env, &init);
			add_history(str);
			//parser(env, &init);
		}
	}
	return(0);
}
