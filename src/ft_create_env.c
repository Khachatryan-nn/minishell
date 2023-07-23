/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:23:59 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/22 22:52:59 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 
#include "minishell.h"

char	*ft_find_symbol(char *str, char c)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = NULL;
	j = 0;
	i = 0;
	while (str[i] != c  && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return(str);
	ptr = (char *)malloc(sizeof(char) * i);
	if (!ptr)
	return(NULL);
	while (j < i)
	{
		ptr[j] = str[j];
		j++;
	}
	ptr[j] = '\0';
	return(ptr);
}

t_list	*ft_lstnew_2(char *str)
{
	t_list	*lst;
	lst = malloc(sizeof(t_list));
	lst->ptr = ft_strdup(ft_find_symbol(str, '='));
	lst->value = ft_strdup(ft_strchr(str, '='));
	lst->type = ft_strdup("yes");
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
		ft_lstadd_back(stack, stack_a);
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
		if (ft_strcmp(lst->type, "yes") == 0)
		{
			printf("%s", lst->ptr);
			printf("%s\n", lst->value);
		}
		(lst) = (lst)->next;
	}
}