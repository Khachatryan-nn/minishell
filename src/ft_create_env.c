/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:23:59 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/22 21:09:29 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_symbol(char *str, char c)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = NULL;
	j = 0;
	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (str);
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	while (j < i)
	{
		ptr[j] = str[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

t_list	*ft_lstnew_2(char *str)
{
	t_list	*lst;
	lst = malloc(sizeof(t_list));
	lst->ptr = ft_strdup(ft_find_symbol(str, '='));
	lst->value = ft_strdup(ft_strchr(str, '='));
	lst->next = NULL;
	lst->prev = NULL;
	return(lst);
}

void	ft_create_env(char **str, t_list **stack)
{
	int		i;
	t_list	*stack_a;

	i = 0;
	while (str[i])
	{
		stack_a = ft_lstnew_2(str[i]);
		if (ft_strcmp(stack_a->ptr, "OLDPWD") != 0)
			ft_lstadd_back(stack, stack_a);
		else
		{
			// free(stack_a->ptr);
			// free(stack_a->value);
			free(stack_a);
		}
		i++;
	}
}

void	ft_env(t_list *env)
{
	t_list	*lst;

	lst = NULL;
	lst = env;
	while ((lst))
	{
		if (lst->ptr && lst->value)
		{
			printf("%s", lst->ptr);
			printf("%s\n", lst->value);
		}
		(lst) = (lst)->next;
	}
}
