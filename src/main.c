/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:33:29 by musimony          #+#    #+#             */
/*   Updated: 2023/06/25 21:30:45 by tikhacha         ###   ########.fr       */
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
	char	*ls;

	(void)	av;
	env = NULL;
	ls = NULL;
	ft_create_env(env1, &env);
	if (ac == 1)
	{
		print_logo();
		while (1)
		{
			str = readline("\033[38;5;46mminishell$ \e[0m");
			if (ft_strcmp(str, "") == 0)
				continue ;
			if (ft_strcmp(str, "env") == 0)
				ft_env(env);
			else if (ft_strcmp(str, "pwd") == 0)
				ft_pwd(env);
			else if (ft_strcmp(str, "exit") == 0)
			//{
			//	system("leaks minishell");
				exit (0);
			//}
			else if (ft_strcmp(str, "ls") == 0)
			{
				ls = ft_ls(ls);
				if (ls)
					printf("%s\n", ls);
				free(ls);
				ls = NULL;
			}
			else if (ft_strnstr(str, "cd", 2))
				ft_cd(env, ft_strchr(str, str[3]));
			else if (ft_onlyspaces(str))
				;
			else
				lex(str, env, env1);
			add_history(str);
		}
	}
}
