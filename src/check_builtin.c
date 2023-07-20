#include "minishell.h"

int check_built(char *str, t_list *env)
{
    char *ls;
    // char *str;

    ls = NULL;
    // str = ft_strdup(cmd->cmd_line);
	if (ft_strcmp(str, "env") == 0)
		{
            ft_env(env);
            return(1);
        }
     if (ft_strnstr(str, "pwd", 3) == 0)
        {
			ft_pwd(env);
            return(1);
        }
    else if (ft_strnstr(str, "export", 6) == 0)
    {
        if(ft_strcmp(str, "export") == 0)
            ft_export(env);
        else
        {
            // ft_export(env);
            ft_export_change(str, env);
        }
        return(1);
    }
    else if (ft_strnstr(str, "unset", 5) == 0)
    {
        ft_unset(str, env);
        return(1);
    }
    else if (ft_strnstr(str, "cd", 2) == 0)
    {
		ft_cd(env, str);
        return(1);
    }
    return(0);
}