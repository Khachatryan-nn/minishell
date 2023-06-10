#include "minishell.h"

t_list *ft_lstnew_2(char *str)
{
    t_list *lst;

    lst = malloc(sizeof(t_list));
    lst->ptr = ft_strdup(str);
    lst->next = NULL;
    lst->prev = NULL;
    return(lst);
}


void    ft_create_env(char **str, t_list **stack)
{
    int     i;
    t_list *stack_a;

    i = 0;
    while (str[i])
    {
        stack_a = ft_lstnew_2(str[i]);
        if (ft_strnstr(stack_a->ptr, "OLDPWD", 10) == NULL)
            ft_lstadd_back(stack, stack_a);
        i++;
    }
}

void    ft_env(t_list *env)
{
    t_list *lst;
	lst = NULL;
    lst = env;
	while ((lst))
   	{
      printf("%s\n", (lst)->ptr);
      (lst) = (lst)->next;
    }
}