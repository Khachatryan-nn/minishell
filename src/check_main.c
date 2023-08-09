#include "minishell.h"

void	ft_check_main(char *str, t_list *env, t_init init)
{
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
		exit(0);
	}
	else if (!ft_onlyspaces(str))
	{
		lex(str, &init);
		check_ast(&init, init.pars, env);
	}
}