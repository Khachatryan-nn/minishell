/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:33:29 by musimony          #+#    #+#             */
/*   Updated: 2023/06/16 16:49:58 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void static	print_logo(void)
{
	printf("\033[38;5;60m%s\n%s\n%s\n%s\n%s\n%s\n\033[0m", \
	"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ", \
	"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     ", \
	"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     ", \
	"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     ", \
	"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗", \
	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝");
}

int main(int ac, char **av, char **env1)
{
	(void)	av;
	char	*str;
	t_list	*env;
	char	*ls;

	env = NULL;
	ls = NULL;
	ft_create_env(env1, &env);
	if (ac == 1)
	{
		print_logo();
		while(1)
		{
			str = readline("minishell>: ");
			if (ft_strcmp(str, "env") == 0)
				ft_env(env);
			if (ft_strcmp(str, "pwd") == 0)
				ft_pwd(env);
			if(ft_strcmp(str, "exit") == 0)
				exit(0);
			if (ft_strcmp(str, "ls") == 0)
			{
				ls = ft_ls(ls);
				if(ls)
					printf("%s\n", ls);
				free(ls);
				ls = NULL;
			}
			if (ft_strnstr(str,"cd", 2))
				ft_cd(env,  ft_strchr(str, str[3]));
			lex(str, env);
			add_history(str);
		}
	}
}
