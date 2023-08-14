/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:50:06 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/09 21:52:32 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		i;
	char	*ptr1;
	char	*ptr2;

	i = 0;
	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	while ((ptr1[i] == ptr2[i]) && n - 1 > i)
	{
		if (ptr1[i] == '\0' && ptr2[i] == '\0')
			return (0);
		i++;
	}
	return (ptr1[i] - ptr2[i]);
}

void	ft_export(t_list *env)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = NULL;
	ptr = ft_export_continue(env);
	i = 0;
	while (ptr[i] != 0)
	{
		printf("declare - x ");
		printf("%s", ft_find_symbol(ptr[i], '='));
		if (ft_strchr(ptr[i], '='))
		{
			printf("=%c", '\"');
			printf("%s", ft_strchr(ptr[i], '=') + 1);
			printf("%c\n", '\"');
		}
		else
			printf("\n");
		free(ptr[i]);
		i++;
	}
	free (ptr);
}

char	**ft_export_continue(t_list *env1)
{
	char	**ptr;
	t_list	*env;
	int		a;

	a = 0;
	ptr = NULL;
	env = NULL;
	env = env1;
	while (env)
	{
		if (env->unset != 1)
		a++;
		env = env->next;
	}
	env = env1;
	ptr = ft_export_continue2(env, env1, ptr, a);
	return (ptr);
}

char	**ft_export_continue2(t_list *env, t_list *env1, char **ptr, int a)
{
	int	i;

	i = 0;
	ptr = (char **)malloc(sizeof(char *) * ft_lstsize(env1) - a + 1);
	while (env)
	{
		if (env->unset == 1 && env1->type == 1)
		{
			ptr[i] = ft_strdup(env->ptr);
			ptr[i] = ft_strjoin(ptr[i], env->value, 0);
			i++;
			env = env->next;
		}
		else
			env = env->next;
	}
	ptr[i] = 0;
	return (ptr);
}
