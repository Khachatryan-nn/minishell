# include "minishell.h"

void    ft_pwd(t_list *env)
{
    char *ptr;
    (void)env;
    ptr = NULL;
    ptr = getcwd(NULL, 0);
    printf("%s\n", ptr);
}