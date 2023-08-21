/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:58:53 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/22 01:30:49 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**restore_cmd_line(t_parser *stack);
char	**env_matrix(t_list *env);

char	**restore_cmd_line(t_parser *stack)
{
	char		**cmd_matrix;
	int			mode;
	t_parser	*ptr;
	int			i;

	ptr = stack;
	i = 0;
	cmd_matrix = (char **) malloc (sizeof(char *) * (lstsize(ptr) + 1));
	if (!cmd_matrix)
		return (NULL);
	while (i < lstsize(ptr))
		cmd_matrix[i++] = NULL;
	i = -1;
	while (ptr && ptr->cmd)
	{
		mode = (ptr->flag & (_ISCMD_)) && 1;
		if (mode == 0 && check_type(ptr->type) == 0)
		{
			if (i < 0)
				i++;
			cmd_matrix[i] = ft_strjoin(cmd_matrix[i], ptr->cmd, 1);
		}
		else
		{
			i++;
			cmd_matrix[i] = ft_strdup(ptr->cmd);
		}
		ptr = ptr->next;
	}
	cmd_matrix[i + 1] = NULL;
	return (cmd_matrix);
}

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
