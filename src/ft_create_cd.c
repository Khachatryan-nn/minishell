#include "minishell.h"

char    *ft_change_str(char *str)
{
    int i;
    int j;
    char *ptr;

    ptr = NULL;
    j = ft_strlen(str);
    while (str[--j])
    {
        if (str[j] == '/')
        {
            ptr = (char *)malloc(sizeof(char) * j);
            i = 0;
            while (i < j)
            {
                ptr[i] = str[i];
                i++;
            }
            ptr[i] = '\0';
            break;
        }
    }
    return(ptr);
}


void    ft_cd(t_list *str, char *text)
{
    static  int k = 0;
    char    *pwd;
    char    *old;
    t_list  *temp;

    pwd = NULL;
    old = NULL;
    temp = NULL;
    temp = str;
    chdir(text);
    if (k == 0)
    {
        ft_lstadd_back(&str, ft_lstnew_2("OLDPWD"));
        k++;
    }
    while (temp)
    {
        if (ft_strnstr(temp->ptr, "PWD", 3))
        {
            old = ft_strdup(ft_strchr(temp->ptr, '='));
            free(temp->ptr);
            temp->ptr = ft_strjoin("PWD=", getcwd(NULL, 0));
        }
        if (ft_strnstr(temp->ptr, "OLD", 3))
        {
            free(temp->ptr);
            temp->ptr = ft_strjoin("OLDPWD", ft_strdup(old));
        }
        temp = temp->next;
    }
}