/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:19:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/26 18:06:58 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shunting_yard(t_tok **p, t_tok **ops, t_tok **otp);
void	parser(t_init *init, t_env *env);
void	push(t_tok **a, t_tok **b);
void	pop(t_tok **stack);

void	pop(t_tok **stack)
{
	t_tok	*temp;

	temp = lstlast(*stack);
	if (!temp)
		*stack = NULL;
	if (temp->prev)
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
	}
	else
		*stack = NULL;
	free (temp->cmd);
	if (temp->hdoc_fname)
		free(temp->hdoc_fname);
	free (temp);
}

void	push(t_tok **a, t_tok **b)
{
	t_tok	*ptr1;
	t_tok	*ptr2;

	ptr1 = lstlast(*a);
	ptr2 = lstlast(*b);
	if (ptr1 == NULL)
		return ;
	if (ptr2)
		ptr2->next = ptr1;
	else
		*b = ptr1;
	if (ptr1->prev)
		ptr1->prev->next = NULL;
	else
		*a = NULL;
	ptr1->prev = ptr2;
}

void	shunting_yard(t_tok **p, t_tok **ops, t_tok **otp)
{
	if ((*p)->prc == 0)
		lstback(otp, ast_branch(*p));
	else if ((*p)->prc > 0)
	{
		if ((*p)->type == SUBSH_CLOSE)
		{
			while (*ops && lstlast(*ops)->type != SUBSH_OPEN)
				push(ops, otp);
			lstlast(*otp)->sub = 1;
			pop(ops);
		}
		else if ((*p)->type != SUBSH_OPEN)
		{
			while (*ops && lstlast(*ops)->prc >= (*p)->prc \
				&& lstlast(*ops)->type != SUBSH_OPEN)
				push(ops, otp);
			lstback(ops, ast_branch(*p));
		}
		else
			lstback(ops, ast_branch(*p));
	}
}

void	parser(t_init *init, t_env *env)
{
	t_tok	*ptr;
	t_tok	*stack_ops;
	t_tok	*stack_otp;

	(void) env;
	stack_ops = NULL;
	stack_otp = NULL;
	ptr = init->lex;
	while (ptr)
	{
		shunting_yard(&ptr, &stack_ops, &stack_otp);
		ptr = ptr->next;
	}
	while (stack_ops)
		push(&stack_ops, &stack_otp);
	init->pars = abstract_syntax_tree(init, &stack_otp);
}
