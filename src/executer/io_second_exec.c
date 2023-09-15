/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_second_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 02:08:43 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/15 02:25:09 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_second_arg(t_init *init, t_tok *stack, t_env *env);
char	*find_second_arg(t_tok *stack);

int	execute_second_arg(t_init *init, t_tok *stack, t_env *env)
{
	char	**args;
	char	*arg;

	arg = find_second_arg(stack);
	if (!arg)
		return (0);
	args = ft_split(arg, , ' ');
	free (arg);
	
}

char	*find_second_arg(t_tok *stack)
{
	char	*str;
	t_tok	*tmp;

	if (!stack->right && lstsize(*stack->right) == 1)
		return (NULL);
	str = NULL;
	tmp = stack->next;
	while (tmp && tmp->flag & (1 << 1))
		tmp = tmp->next;
	if (!tmp || tmp->type == END)
		return (NULL);
	str = ft_strdup(tmp->cmd);
	while (tmp && !check_type(tmp->type))
	{
		if (tmp->flag && 1 << 1)
			strjoin_helper(str, tmp->cmd, 2);
		else
			ft_strjoin(str, tmp->cmd, 1);
	}
	return (str);
}

