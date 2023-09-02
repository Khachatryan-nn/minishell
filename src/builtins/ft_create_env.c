/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:23:59 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/02 12:34:02 by tikhacha         ###   ########.fr       */
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
	while (str[i] != c && str[i] != '\0')
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

t_lst	*ft_lstnew_2(char *str)
{
	t_lst	*lst;

	lst = malloc(sizeof(t_lst));
	lst->ptr = ft_strdup(ft_find_symbol(str, '='));
	lst->value = ft_strdup(ft_strchr(str, '='));
	lst->type = 1;
	lst->flag = 1;
	lst->unset = 1;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void	ft_create_env(char **str, t_lst **stack)
{
	int		i;
	int		flag;
	t_lst	*stack_a;

	i = 0;
	flag = 0;
	stack_a = NULL;
	while (str[i])
	{
		stack_a = ft_lstnew_2(str[i]);
		ft_lstadd_back(stack, stack_a);
		if (ft_strcmp(stack_a->ptr, "OLDPWD") == 0)
			flag = 1;
		i++;
	}
	if (flag == 0)
	{
		stack_a = ft_lstnew_2("OLDPWD");
		stack_a->value = ft_strdup("\0");
		stack_a->flag = 0;
		ft_lstadd_back(stack, stack_a);
	}
	stack_a = ft_lstnew_2("?=0");
	{
		ft_lstadd_back(stack, stack_a);
		stack_a->type = 0;
		stack_a->flag = 0;
		stack_a->unset = 0;
	}
}

void	ft_env(t_lst *env)
{
	t_lst	*lst;

	lst = NULL;
	lst = env;
	while ((lst))
	{
		if (lst->type > 0 && lst->flag > 0 && lst->unset > 0
			&& lst->ptr && lst->value)
		{
			printf("%s", lst->ptr);
			printf("%s\n", ft_strchr(lst->value, '='));
		}
		(lst) = (lst)->next;
	}
}
