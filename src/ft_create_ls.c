/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:16:12 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/16 15:16:32 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_ls(char *str) {
    DIR				*dir;
    struct dirent	*entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        printf("Contents of current directory:\n");
        return(NULL);
    }
    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_name[0] != '.' && !ft_strnstr(entry->d_name, \
		"minishell", ft_strlen(entry->d_name)))
        {
            str = ft_strjoin(str, entry->d_name);
            str = ft_strjoin(str, "\t");
        }
    }
    closedir(dir);
    return(str);
}