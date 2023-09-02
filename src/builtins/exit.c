#include "minishell.h"

void	ft_exit(t_lst *env, t_init *init)
{
	t_init	*lst;
	char	*str;

	lst = NULL;
	lst = init;
	lst->lex = lst->lex->next;
	if (ft_strcmp(lst->lex->cmd, "AST") == 0)
	{
		exit_env(0, env);
		exit(0);
	}
	if (lst->lex->cmd[0] == '\0')
	{
			printf("exit\n");
			printf("minishell$: exit: : numeric argument required\n");
			exit_env(255, env);
		 	exit (255);		
	}
	while (ft_strcmp(lst->lex->cmd, "AST") != 0)
	{
		str = ft_strdup(lst->lex->cmd);
		while (*str == '0')
			str++;
		ft_check_valid(str, env);
		ft_check_valid_2(str, env);
		ft_check_valid_3(lst, env);
		free(str);
		lst->lex = lst->lex->next;
	}
}

void	exit_env(int a, t_lst *env)
{
	t_lst *lst;
	char	*ptr;

	lst = NULL;
	lst = env;
	ptr = ft_itoa(a);
	while (lst)
	{
		if (ft_strcmp(lst->ptr, "?") == 0)
		{
			lst->value = ft_strdup(ptr);
			break;
		}
		lst = lst->next;
	}
	free(ptr);
}

int	ft_atoi_2(long long a)
{
	if (a % 256 > 0)
		return (a % 256);
	else if (a % 256 < 0)
		return (256 + a);
	else
		return (0);
}

void	ft_check_valid(char *str, t_lst *env)
{
	int	i;

	i = 0;
		if (str[0] == '-' ||str[0] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
		{
			printf("exit\n");
			printf("minishell$: exit: %s: numeric argument required\n",str);
			exit_env(255, env);
		 	exit (255);
		}
		i++;
	}
}

void	ft_check_valid_2(char *str, t_lst *env)
{
	if (str[0] == '-')
	{
		if (ft_strlen(str) > 20 || ft_strcmp(str, "-9223372036854775808") > 0)
		{
			printf("exit\n");
			printf("minishell$: exit: %s: numeric argument required\n",str);
			exit_env(255, env);
			exit (255);				
		}
	}
	else
	{
		if (ft_strlen(str) > 20 || ft_strcmp(str, "9223372036854775807") > 0)
		{
			printf("exit\n");
			printf("minishell$: exit: %s: numeric argument required\n",str);
			exit_env(255, env);
			exit (255);				
		}		
	}
}

void	ft_check_valid_3(t_init *lst, t_lst *env)
{
	if (ft_strcmp(lst->lex->next->cmd, "AST") != 0)
		{
			printf("exit\n");
			printf("minishell$: exit: too many arguments\n");
			exit_env(1, env);
 			exit(1);
		}
	else
		{
			exit_env(ft_atoi_2(ft_atoi(lst->lex->cmd)), env);
 			exit(ft_atoi_2(ft_atoi(lst->lex->cmd) % 256));		
		}
}