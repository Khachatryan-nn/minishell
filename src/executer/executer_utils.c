/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:58:53 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/27 17:17:45 by tikhacha         ###   ########.fr       */
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
			(ptr->type == DQUOTE || ptr->type == SQUOTE)))
			cmd = ft_strjoin(cmd, ptr->cmd, 1);
		else
			cmd = strjoin_helper(cmd, ptr->cmd, 0);
		ptr = ptr->next;
	}
	return (cmd);
}
