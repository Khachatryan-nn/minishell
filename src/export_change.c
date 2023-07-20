#include "minishell.h"

void    ft_export_change(char *line, t_list *env)
{
    int i;
    int j;
    int k;
    char *str;
    char    *ptr;
    char    **ttr;
    t_list *stack_a;

    i = 1;
    j = 0;
    k = 0;
    ttr = (char **)malloc(sizeof(char *) * 1000);
    ptr = (char *)malloc(sizeof(char) * 1000);
    str = ft_strchr(line, 't');
    while (str[i] != '\0')
    {
        j = 0;
         while (str[i] != '\0' && str[i] == ' ')
            i++;
         while (str[i] != '\0' && str[i] != ' ')
         {
            if (str[i] == '"')
            {
                i++;
             while (str[i] != '"' && str[i] != '\0')
            {
                ptr[j] = str[i];
                i++;
                j++;
            }
            i++;
            }
            if (str[i] != '\0' && str[i] != ' ')
            {
                ptr[j] = str[i];
                i++;
                j++;
            }
         }
         ptr[j] = '\0';
         ttr[k] = ft_strdup(ptr);
         k++;
    }
         ttr[k] = 0;
         k = 0;
         j = 0;
         while (ttr[k])
         {
            if (((ttr[k][j] >= 65 && ttr[k][j] <= 90) || (ttr[k][j] >= 97 && ttr[k][j] <= 122) || ttr[k][j] == 95))
            {
                stack_a = ft_lstnew_2(ttr[k]);
                if (!ft_list_change(stack_a, env))
                ft_lstadd_back(&env, stack_a);
                free(ttr[k]);
            }
            else
            {
                printf("minishell$ export: `%s': not a valid identifier\n", ttr[k]);
                free(ttr[k]);
            }
            k++;
         }
         while (ttr[k])
         {
            free(ttr[k]);
            k++;
         }
         free(ttr);
         free(ptr);

}
    

int    ft_list_change(t_list *new, t_list *env)
{
    t_list *str;

    str = env;

    while (str)
    {
        if (ft_strcmp(new->ptr, str->ptr) == 0)
            {
                str->value = ft_strdup(new->value);
                return(1);
            }
        str = str->next;
    }
    return(0);
}