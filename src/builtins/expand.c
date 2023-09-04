/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:43 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 15:08:02 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr2(char *s1, int i, int j)
{
	char	*str;
	int		a;

	str = NULL;
	a = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen2(s1) - i + j + 1));
	while (j > 0)
	{
		str[a] = s1[i];
		a++;
		i++;
		j--;
	}
	str[a] = '\0';
	return(str);
}

char	*ft_check_str(char *str)
{
	int	i;
	int	j;
	char	*ptr;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] != '\0' && str[i] != 39)
				i++;
			if (str[i] == 39)
				i++;
		}
		if (str[i] == 34)
			j++;
		i++;
	}
	if (j > 0)
	{
		printf("%d\n", j);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen2(str) - j + 1));
	i = 0;
	j = 0;
		while (str[i] != '\0')
	{
		if (str[i] == 39)
			i++;
		if (str[i] != '\0')
			ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	printf("----%s\n", ptr);
	free(str);
	return(ptr);
	}
	return(str);
}


char	*ft_expand(char *str, t_lst *env)
{
	char	*ptr;
	char	*ttr;
	int		i;
	int		j;
	int		end;
	int		flag;

	i = 0;
	end = 0;
	j = 0;
	flag = 0;
	ttr = NULL;
	ptr = NULL;
	(void)env;
	if (!str)
		return (NULL);
	if (ft_strchr(str, '\"'))
		str = ft_check_str(str);
	while (str && str[i] != '\0')
	{
		if (str && str[i] == '\'')
		{
			i++;
			while (str[i] != '\0' && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		if(str[i] == '$')
		{
			printf("aaa\n");
			ttr = expand_change(str, i + 1, env);
			printf("!!%c!!\n", str[i]);
			end = 0;
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != 34)
			{
				if (str[i] == 39)
				{
					while (str[i] != '\0' && str[i] != 39)
						i++;
					if (str[i] == 39)
					i++;
					flag = 1;
				}
				i++;
				end++;
			}
			if (flag == 0)
			{
			ptr = (char *)malloc(sizeof(char) * (ft_strlen2(str) - end + ft_strlen2(ttr) + 1));
			end = 0;
			j = 0;
			while (str[end] != '$')
			{
				if (str[i] == 39)
				{
					while (str[i] != '\0' && str[i] != 39)
						i++;
					if (str[i] == 39)
					i++;
				}
				ptr[end] = str[end];
				end++;
			}
			while (ttr[j] != '\0')
			{
				ptr[end] = ttr[j];
				end++;
				j++;
			}
			while(str[i] != '\0')
			{
				ptr[end] = str[i];
				end++;
				i++;
			}
			ptr[end] = '\0';
			str = ft_strdup(ptr);
			free(ptr);
			}
		 }
		i++;
	}
	return(str);
}

char	*expand_change(char *str, int i, t_lst *env)
{
	int		j;
	t_lst *lst;
	char	*ptr;

	j = i;
	ptr = NULL;
	lst = NULL;
	lst = env;
	while (str[j] != '\0' && str[j] != ' ' && str[j] != '|' && str[j] != '<' && str[j] != '>' && str[j] != '\"')
	{
		j++;
	}
	ptr = ft_substr2(str, i, j - i);
	ptr = ft_substr(str, i, j - i);
	while (lst)
	{
		if (ft_strcmp(lst->ptr, ptr) == 0)
		{
			ptr = ft_strdup(lst->value + 1);
			break ;
		}
		lst = lst->next;
	}
	if (!lst)
		ptr = ft_strdup("$");
	return(ptr);
}
