/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 22:10:05 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 00:08:06 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_expand(t_tok *stack, t_env *env);
void	destroy_exp(t_exp *exp);

void	do_expand(t_tok *stack, t_env *env)
{
	t_tok	*tmp;
	char	*str;
	t_exp	exp;

	tmp = stack;
	exp.i = -1;
	exp.l = 0;
	exp.str = NULL;
	exp.s = NULL;
	str = NULL;
	while (tmp)
	{
		if (ft_strchr(tmp->cmd, '$') && tmp->type != SQUOTE)
		{
			str = ft_strdup(expand(tmp->cmd, env, &exp));
			free(tmp->cmd);
			tmp->cmd = ft_strdup(str);
			free(str);
			destroy_exp(&exp);
		}
		tmp = tmp->next;
	}
}

void	destroy_exp(t_exp *exp)
{
	if (exp->i)
		exp->i = -1;
	if (exp->l)
		exp->l = 0;
	if (exp->str)
	{
		free(exp->str);
		exp->str = NULL;
	}
	if (exp->s)
	{
		free(exp->s);
		exp->s = NULL;
	}
}