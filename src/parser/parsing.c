/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:19:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/04 20:44:30 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shunting_yard(t_parser **p, t_parser **ops, t_parser **otp);
void	parser(t_init *init);
void	push(t_parser **a, t_parser **b);
void	pop(t_parser **stack);

void	pop(t_parser **stack)
{
	t_parser	*temp;

	temp = lstlast(*stack);
	if (temp->prev)
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
		free (temp);
	}
	else
		*stack = NULL;
}

void	push(t_parser **a, t_parser **b)
{
	t_parser	*ptr1;
	t_parser	*ptr2;

	ptr1 = lstlast(*a);
	ptr2 = lstlast(*b);
	if (ptr1 == NULL)
		return ;
	else
	{
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
}

void	shunting_yard(t_parser **p, t_parser **ops, t_parser **otp)
{
	if ((*p)->prc == 0)
	{
		lstback(otp, lstnew_pars((*p)->cmd, \
		(*p)->type, (*p)->prc, (*p)->flag));
	}
	else if ((*p)->prc > 0)
	{
		if ((*p)->type == SUBSH_CLOSE)
		{
			while (*ops && lstlast(*ops)->type != SUBSH_OPEN)
				push(ops, otp);
			pop(ops);
			lstlast(*otp)->subshell_code = 1;
			// lstlast(*otp)->flag = lstlast(*otp)->flag + (1 << 6);
		}
		else if ((*p)->type != SUBSH_OPEN)
		{
			while (*ops && lstlast(*ops)->prc >= (*p)->prc \
				&& lstlast(*ops)->type != SUBSH_OPEN)
				push(ops, otp);
			lstback(ops, lstnew_pars((*p)->cmd, \
				(*p)->type, (*p)->prc, (*p)->flag));
		}
		else
			lstback(ops, lstnew_pars((*p)->cmd, (*p)->type, (*p)->prc, \
			(*p)->flag));
	}
}

void	parser(t_init *init)
{
	t_parser	*ptr;
	t_parser	*stack_ops;
	t_parser	*stack_otp;

	ptr = init->lex;
	init->pars = NULL;
	stack_ops = NULL;
	stack_otp = NULL;
	while (ptr)
	{
		shunting_yard(&ptr, &stack_ops, &stack_otp);
		ptr = ptr->next;
	}
	while (stack_ops)
		push(&stack_ops, &stack_otp);
	print_types(stack_otp);
	init->pars = abstract_syntax_tree(init, &stack_otp);
	print_ast(init->pars, 0, 0);
}
