/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:58:53 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/16 17:44:32 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*restore_cmd_line(t_parser *stack);

char	*restore_cmd_line(t_parser *stack)
{
	char		*cmd;
	int			mode;
	t_parser	*ptr;

	cmd = NULL;
	ptr = stack;
	while (ptr && ptr->cmd)
	{
		mode = (ptr->flag & (1 << 1)) && 1;
		if (!cmd || (mode == 0 && \
			check_type(ptr->type) == 0))
			cmd = ft_strjoin(cmd, ptr->cmd, 1);
		else
			cmd = strjoin_helper(cmd, ptr->cmd, 0);
		ptr = ptr->next;
	}
	cmd[ft_strlen(cmd)] = '\0';
	return (cmd);
}

char	**env_matrix(t_list *env)
{
	char	**str;
	t_list	*ptr;
	int		i;

	ptr = env;
	i = 0;
	str = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (ptr)
	{
		//i = 
	}
}
