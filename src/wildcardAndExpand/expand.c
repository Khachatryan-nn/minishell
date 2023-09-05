/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:09:43 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/05 13:19:12 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    do_expand(t_tok *stack, t_env *env);
char    *expand(char *str, t_env **env);
int     only_dollar(char *str);

int only_dollar(char *str)
{
    int i = 0;
    while (str && str[i])
    {
        if (str[i] != '$')
            return (0);
        i++;
    }
    return (1);
}

char *expand(char *str, t_env **env)
{
    int i = -1;
    int l = 0;
    t_env *tmp;

    char *result = NULL;
    char *segment = NULL;
    if (only_dollar(str))
        return (ft_strdup(""));
    while (str[++i])
    {
        if (str[i] == '$')
        {
            if (i > 0 && !result)
                result = ft_substr(str, 0, i);
            else if (str[i + 1] != '\0')
            {
                segment = ft_substr(str, l, i - l);
                result = ft_strjoin(result, segment, 1);
                free(segment);
            }
            i++;
            if (!ft_isalpha(str[i]) && str[i] != '?')
                result = ft_strjoin(result, "$", 1);
            l = i;
            while (str[l] != '\0' && str[l] != '$' && str[l] != ' ' && str[l] != '\'')
                l++;
            tmp = (*env);
            segment = ft_substr(str + i, 0, l - i);
            while (tmp)
            {
                if (str[i] == '?')
                {
                    if (!ft_strcmp(tmp->key, "$?"))
                        result = ft_strjoin(result, tmp->data, 1);
                }
                else if (l - i != 0 && !ft_strcmp(segment, tmp->key))
                    result = ft_strjoin(result, tmp->data, 1);
                tmp = tmp->next;
            }
            i = l;
            free(segment);
        }
        if (!ft_strchr(str + l, '$'))
        {
            result = ft_strjoin(result, str + i, 1);
            break  ;
        }
        else if (str[i] != '$')
        {
            i = l;
            while (str[l] && str[l] != '$')
                l++;
            segment = ft_substr(str, i, l - i);
            result = ft_strjoin(result, segment, 1);
            free(segment);
            i = l - 1;
        }
    }
    return (result);
}

void do_expand(t_tok *stack, t_env *env)
{
    t_tok *tmp = stack;

    while (tmp)
    {
        if (ft_strchr(tmp->cmd, '$') && tmp->type != SQUOTE)
        {
            char *expanded = expand(tmp->cmd, &env);
            free(tmp->cmd);
            tmp->cmd = ft_strdup(expanded);
            free(expanded);
        }
        tmp = tmp->next;
    }
}
