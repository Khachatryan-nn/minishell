/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:52:40 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/02 12:34:02 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_lst *env, t_init *init)
{
	t_init *str;

	str = NULL;
	str = init;
	str->lex = str->lex->next;
	while (ft_strcmp(str->lex->cmd, "AST") != 0 && str->lex->cmd)
	{
		if (ft_strchr(str->lex->cmd, '$'))
			ft_echo_dollar(str->lex->cmd, env);
		else
		{
			printf("%s", str->lex->cmd);
			if (str->lex->next)
			printf(" ");
		}
		str->lex = str->lex->next;
	}
	printf("\n");
}

void	ft_echo_dollar(char *str, t_lst *env)
{
	int		i;
	int		start;
	int	j;
	char	*ptr;

	i = 0;
	j = 0;
	start = 0;
	while (str[i + j] != '\0')
	{
		j = 0;
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] == '?')
		{
			ft_find_env_echo(env);
			i += 2;
		}
		if (str[i] == '$')
		{
			i++;
			start = i;
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
			{
				i++;
				j++;
			}
			ptr = ft_substr(str, start, j);
			if (ft_strlen(ptr) > 2)
			{
				if (((ptr[0] >= 65 && ptr[0] <= 90) ||
				(ptr[0] >= 97 && ptr[0] <= 122) ||
				ptr[0] == 95))
				ft_check_echo_env(ptr, env);
				else
				printf("$%s", ptr);
			}
			else if (ft_strlen(ptr) < 2)
				{
					start = i;
					while (str[start] != '\0')
					{
						if (str[start] != ' ' || str[start] != '$')
							break;
					}
					if (str[start] == '\0')
					printf("$");
				}
		}
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
	free(ptr);
}

void	ft_check_echo_env(char *str, t_lst *env)
{
	t_lst *lst;

	lst = NULL;
	lst = env;
	while (lst)
	{
		if (!ft_strcmp(lst->ptr, str))
		{
			if (lst->value)
				printf("%s", lst->value + 1);
			break;
		}
		lst = lst->next;
	}
}

void	ft_find_env_echo(t_lst *env)
{
	t_lst *lst;

	lst = NULL;
	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->ptr, "?") == 0)
		{
			if (lst->value)
				printf("%s", lst->value);
		}
		lst = lst->next;
	}
}