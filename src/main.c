/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:33:29 by musimony          #+#    #+#             */
/*   Updated: 2023/07/24 15:04:16 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void static	print_logo(void)
{
	write (1, "\033[38;5;60m\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
\033[0m", 1082);
}

int	main(int ac, char **av, char **env1)
{
	char	*str;
	t_list	*env;

	(void)	av;
	env = NULL;

	ft_create_env(env1, &env);

	if (ac == 1)
	{
		print_logo();
		while (1)
		{
			str = readline("minishell$ ");
			if (ft_strcmp(str, "exit") == 0)
			{
				while (env)
				{
					free(env->ptr);
					free(env->value);
					env = env->next;
				}
				return(1);
			}
			if (ft_strcmp(str, "ls"))
				ft_ls(str);

			if (!ft_onlyspaces(str))
				lex(str, env);
			add_history(str);
		}
	}
	return(0);
}
