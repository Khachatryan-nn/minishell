/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:50:06 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/27 16:36:17 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1,  char *s2, int n)
{
	int			i;
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


void    ft_export(t_list *env)
{
    int i;
    int j;
    char **ptr;
    char *swap;
    t_list *env1;

    i = 0;
    j = 0;
    env1 = env;
    ptr = NULL;
    ptr = (char **)malloc(sizeof(char *) * ft_lstsize(env) + 1);
    while (i < ft_lstsize(env))
    {
            if (env1->ptr != NULL)
             ptr[i] = ft_strdup(env1->ptr);
            if (env1->value != NULL)
             ptr[i] = ft_strjoin(ptr[i], ft_strdup(env1->value), 0);
        i++;
        env1 = env1->next;
    }
    ptr[i] = 0;
    i = -1;
    while (++i < ft_lstsize(env))
    {
        j = 0;
        while (ptr[j] && ptr[j + 1] && ptr)
        {
            if (ft_strncmp(ptr[j], ptr[j + 1], ft_strlen(ptr[j])) > 0)
            {
                swap = ptr[j];
                ptr[j] = ptr[j + 1];
                ptr[j + 1] = swap;
            }
            j++;
        }
        i++;
    }
    i = 0;
    env1 = env;
    while (ptr[i] != '\0' && *ptr != NULL && env1)
    {
        if (env1->type == 1 && env1->flag == 1)
        {
            printf("declare - x ");
            printf("%s", ft_find_symbol(ptr[i], '='));
            if(ft_strchr(ptr[i], '='))
                 printf("= \"%s\"\n", (ft_strchr(ptr[i], '=') + 1));
             else
             printf("\n");
        }
             i++;
             env1 = env1->next;
    }
    i = 0;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
}
