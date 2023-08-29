/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:58:53 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/30 01:39:27 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_matrix(t_list *env);
char	*handle_heredoc_input(char *string);
void	handle_dollar(int exit_status, t_list **env);

char	**env_matrix(t_list *env)
{
	char	**tmp;
	t_list	*ptr;
	int		i;

	ptr = env;
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (ptr)
	{
		if (ptr->ptr && ptr->value)
		{
			tmp[i] = ft_strjoin(ptr->ptr, ptr->value, 0);
			i++;
		}
		ptr = ptr->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	*handle_heredoc_input(char *string)
{
	char	*line;
	char	*res;

	line = NULL;
	res = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, string) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (!res)
			res = ft_strdup(line);
		else
			res = strjoin_helper(res, line, 1);
		free(line);
	}
	if (!res)
		ft_strdup("");
	else
		res = ft_strjoin(res, "\n", 1);
	return (res);
}

void	handle_dollar(int exit_status, t_list **env)
{
	t_list	*tmp;
	char	*status;

	tmp = (*env);
	status = ft_itoa(exit_status);
	while (tmp)
	{
		if (!ft_strcmp(tmp->ptr, "$?"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(status);
			break ;
		}
		tmp = tmp->next;
	}
	free(status);
}
