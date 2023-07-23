/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:59:54 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/22 23:00:05 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 
#include "minishell.h"

void ft_unset(char *ptr, t_list *env)
{
    t_list  *lst;
    char    **ttr;
    char    *str;
    t_list  *swap;
    t_list *swap1;

    int     i;
    int     j;
    int     k;

    i = 0;
    j = 0;
    k = 0;
    ttr = NULL;
    swap = NULL;
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
    // k = 0;
    // while (ttr[k])
    // {
    //     printf("%s\n", ttr[k]);
    //     k++;
    // }
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
        swap = NULL;
        swap1 = NULL;
        lst = env;
        while (lst)
        {
            if(ft_strcmp(lst->ptr, ttr[k]) == 0)
            {
                lst->type = ft_strdup("no");
                printf("%s\n", lst->type);
            }
            lst = lst->next;
        }
        k++;
   }
}