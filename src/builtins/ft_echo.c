#include "minishell.h"

int	ft_check_echo(char *str, t_list *env)
{
	t_list *list;
	char	*ptr;

	list = env;
	ptr = NULL;
	ptr = str;
	if (ft_strchr(str, ' '))
	{
		ptr = ft_strdup(ft_find_symbol(str, ' '));
		ptr++;
	}
	else
		ptr++;
	if (ptr)
		{
			while (list)
			{
				if (ft_strcmp(list->ptr, ptr) == 0)
				{
					if(list->value)
					{
						printf("%s", list->value + 1);
						if (ft_strchr(str, ' '))
						{
							printf("%s ", ft_strchr(str, ' '));
						}
					}
					return(1);
				}
				list = list->next;
			}
		}
	return (0);
}

void	ft_echo(t_list *env, t_init *init)
{
	t_init *str;
	int		i;

	str = NULL;
	str = init;
	(void) env;
	i = 0;
	str->lex = str->lex->next;
	while (ft_strcmp(str->lex->cmd, "AST") != 0 && str->lex->cmd)
	{
		if (ft_strchr(str->lex->cmd, '$'))
		;
			// ft_echo_dollar(str->lex->cmd, env);
		// else if (ft_strchr(str->lex->cmd, '\\'))
		// 	{
		// 		printf("%s", ft_find_symbol(str->lex->cmd, '\\'));
		// 		printf("%s", ft_strchr(str->lex->cmd, '\\') + 1);
		// 	}
		else
		{
			while(str->lex->cmd[i] != '\0')
			{
				// if (str->lex->cmd[i] == '\\')
				// {
				// 	ft_check_slash(str);
				// }
				// printf("%c", str->lex->cmd[i]);
				i++;
			}
		}
		str->lex = str->lex->next;
	}
	printf("\n");
}

void	ft_check_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1] == '\\' && str[i + 1])
			{
				while (str[i] != '\0' && str[i] == '\\')
					i++;
				printf("%c", '\\');
			}
		else
			i++;
		if (str[i] != '\0')
			printf("%c", str[i]);
	}
}

void	ft_echo_dollar(char *str, t_list *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void) str;
	(void) env;
	// if (ft_strchr(str, '\\'))
	// {
	// 	while (str[i] != '$' && str[i] != '\0')
	// 		i++;
	// 	while (str[j] != '\\' && str[j] != '\0')
	// 		j++;
	// 	if (i = j - 1 || j = i - 1)
	// 		{
	// 			i = 0;
	// 			while (str[i] != '\0')
	// 			{
	// 				if (str[i] == '\\')
	// 					i++;
	// 				if (str[i] != '\0')
	// 					printf("%c", str[i]);
	// 				i++;
	// 			}
	// 		}
	// }
				}