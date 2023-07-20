/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:17:48 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/21 00:51:22 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_list *str, char *ptr)
{
	char	*text;
	int		i;
	int		j;

	j = 0;
	i = 0;
	text = NULL;
	while (ptr[i] != '\0' && ptr[i] == ' ')
		i++;
	text = (char *)malloc(sizeof(char) * (ft_strlen(ptr + i) + 1));
	while (ptr[i] != '\0' && ptr[i] != ' ')
	{
		text[j] = ptr[i];
		i++;
		j++;
	}
	text[j] = '\0';
	//while (ptr[i] != '\0' && ptr[i] != ' ')
	//	i++;
	//while (ptr[i] != '\0' && ptr[i] == ' ')
	//{
	//	text[j] = ptr[i];
	//	i++;
	//	j++;
	//}
	// if (ft_strcmp(text, "..") == 0)
	// 	ft_cd_prev(str, text);
	 if (ft_ls(text) != NULL)
		ft_cd_prev(str, text);
	else
		printf("no such file directory\n");
	if (text)
	{
		free (text);
		text = 0;
	}
}

void	ft_cd_prev(t_list *str, char *text)
{
	t_list		*temp;
	static int	k = 0;
	char		*old;

	temp = NULL;
	old = NULL;
	chdir(text);
	temp = str;
	while ((temp))
	{
		if (ft_strnstr(temp->ptr, "PWD", 3) == 0)
		{
			old = ft_strdup(temp->value);
			free(temp->value);
			temp->value = ft_strdup(ft_strjoin("=", getcwd(NULL, 0)));
			break;
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
			if (ft_strnstr(temp->ptr, "OLDPWD", 6) == 0)
			{
				// temp->ptr = ft_strdup("OLDPWD");
				temp->value = ft_strdup(old);
				break ;
			}
			temp = temp->next;
		}
	}
}
