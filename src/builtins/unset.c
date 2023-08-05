#include "minishell.h"

void ft_unset(char *ptr, t_list *env, t_init *init)
{
    t_list  *lst;
    char    **ttr;
    char    *str;

    int     flag1;
    int     i;
    int     j;
    int     k;

    i = 0;
    j = 0;
    k = 0;
    flag1 = 0;
    lst = NULL;
    ttr = NULL;
    str = (char *)malloc(sizeof(char) * 1000);
    while (ptr[i] == ' ' && ptr[i] != '\0')
    i++;
    while (ptr[i] != ' ' && ptr[i] != '\0')
    i++;
    while (ptr[i] != '\0')
    {
        str[j] = ptr[i];
        i++;
        j++;
    }
    i = 0;
    if(str[i] != '\0')
    {
    ttr = (char **)malloc(sizeof(char *) * 1000);
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
    }
    k = 0;
   while (ttr[k] && *ttr)
   {
        j = 0;
        if (!((ttr[k][j] >= 65 && ttr[k][j] <= 90) ||(ttr[k][j] >= 97 && ttr[k][j] <= 122) || ttr[k][j] == 95))
        {
            printf("minishell$ unset: `%s': not a valid identifier\n", ttr[k]);
            k++;
            continue;
        }
        while (ttr[k][j] != '\0')
        {
            if (ttr[k][j] == ' ')
                break;
            j++;
        }
        if (ttr[k][j] == ' ')
        {
            printf("minishell$ unset: `%s': not a valid identifier\n", ttr[k]);
            k++;
            continue;
        }
        lst = env;
        while (lst)
        {
            if(ft_strcmp(lst->ptr, ttr[k]) == 0)
            {
                if (ft_strcmp(ttr[k], "PATH") == 0)
                    init->flag = 2;
                 lst->type = 0;
                 lst->flag = 0;
                 lst->unset = 0;
            }
            lst = lst->next;
        }
        if (flag1 == 1)
        {
            lst = env;
            while (lst)
            {
                if (ft_strcmp(lst->ptr, "OLDPWD") == 0)
                    {
                        lst->value = ft_strdup("=");
                        lst->unset = 1;
                        break;
                    }
                lst = lst->next;
            }
        }
        k++;
   }
}