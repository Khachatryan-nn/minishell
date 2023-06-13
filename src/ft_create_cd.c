#include "minishell.h"

void    ft_cd(t_list *str, char *text)
{
    if(ft_strcmp(text, "..") == 0)
        ft_cd_prev(str, text);
    else if (ft_ls(text) != NULL)
        ft_cd_prev(str, text);
    else
        printf("no such file directory\n");
}

void    ft_cd_prev(t_list *str, char *text)
{
    t_list *temp;
    static int k = 0;
    char *old;

    temp = NULL;
    old = NULL;
    chdir(text);
    temp = str;
            while ((temp))
        {
            if (ft_strnstr(temp->ptr, "PWD", 3))
            {
                old = ft_strdup(temp->value);
                free(temp->value);
                temp->value = ft_strdup(ft_strjoin("=", getcwd(NULL, 0)));
            }
            temp = temp->next;
        }
        if (k == 0)
        {
            ft_lstadd_back(&str, ft_lstnew_2(ft_strjoin("OLDPWD", old)));
            k++;
        }
        else
        {
            temp = str;
            while (temp)
            {
                if (ft_strnstr(temp->ptr, "OLD", 3))
                {
                temp->ptr = ft_strdup("OLDPWD");
                temp->value = ft_strdup(old);
                break;
                }
                temp = temp->next;
            }
        }
}