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
    int a;
    char    **ptr;
    t_list  *env1;

    i = 0;
    a = 0;
    env1 = NULL;
    ptr = NULL;
    env1 = env;
    while (env1)
    {
        if (env1->unset != 1)
            a++;
        env1 = env1->next;
    }
    ptr = (char **)malloc(sizeof(char *) * ft_lstsize(env) - a + 1);
    env1 = env;
    while (env1)
    {
        if (env1->unset == 1 && env1->type == 1)
        {
            ptr[i] = ft_strdup(env1->ptr);
            ptr[i] = ft_strjoin(ptr[i], env1->value, 0);
            i++;
            env1 = env1->next;
        }
        else
            env1 = env1->next;
    }

    ptr[i] = 0;

    i = 0;
    while (ptr[i] != '\0')
    {
            printf("declare - x ");
            printf("%s", ft_find_symbol(ptr[i], '='));
            if(ft_strchr(ptr[i], '='))
            {
                printf("=%c", '\"');
                printf("%s", ft_strchr(ptr[i], '=') + 1);
                printf("%c\n", '\"');
            }
            else
                printf("\n");
             i++;
    }
	i = -1;
	while (ptr[++i])
	free(ptr[i]);
	free(ptr);
	env1 = env;
	env1 = NULL;

}
