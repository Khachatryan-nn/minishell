/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:19:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/22 21:06:01 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_list *env, t_init *init);
void	push(t_parser **a, t_parser **b);
void	pop(t_parser **stack);

void	pop(t_parser **stack)
{
	t_parser	*temp;

	temp = lstlast_pars(*stack);
	if (temp->prev)
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
	}
	else
		*stack = NULL;
}

void	push(t_parser **a, t_parser **b)
{
	t_parser	*ptr1;
	t_parser	*ptr2;

	ptr1 = NULL;
	ptr2 = NULL;
	//printf("segfault caused by:\n"); print_types(*a); print_types(*b);
	//[%s] and [%s]\n", lstlast_pars(*a)->cmd, lstlast_pars(*b)->cmd);
	if (lstsize_pars(*a) == 0)
		return ;
	else if (lstsize_pars(*a) == 1 && lstsize_pars(*b) == 0)
	{
		*b = *a;
		*a = NULL;
	}
	else if (lstsize_pars(*a) == 1 && lstsize_pars(*b) > 0)
	{
		ptr1 = lstlast_pars(*b);
		ptr1->next = *a;
		(*a)->prev = ptr1;
		*a = NULL;
	}
	else if (lstsize_pars(*a) > 1 && lstsize_pars(*b) > 0)
	{
		ptr1 = lstlast_pars(*b);
		ptr2 = lstlast_pars(*a);
		ptr1->next = ptr2;
		ptr2->prev->next = NULL;
		ptr2->prev = ptr1;
	}
	else
		return ;
}

void	parser(t_list *env, t_init *init)
{
	t_lexargs	*ptr;
	t_parser	*stack_ops;
	t_parser	*stack_otp;

	(void)	env;
	ptr = init->lex;
	stack_ops = NULL;
	stack_otp = NULL;
	while (ptr)
	{
		//printf("\n\t\tprocessing type is:\t%s\n", ptr->cmd);
		//printf("%p\tstack_otp:\t\t", &ptr); print_types(stack_otp);
		//printf("\t\tstack_ops:\t\t"); print_types(stack_ops);
		if (ptr->prc == 0)
		{
			lstback_pars(&stack_otp, lstnew_pars(ptr->cmd, \
			ptr->type, ptr->prc));
		}
		else if (ptr->prc > 0)
		{
			if (ptr->type == SUBSH_CLOSE)
			{
				while (stack_ops && lstlast_pars(stack_ops)->type != SUBSH_OPEN)
					push(&stack_ops, &stack_otp);
				pop(&stack_ops);
			}
			else if (ptr->prc > 1)
			{
				while (stack_ops && lstlast_pars(stack_ops)->prc >= ptr->prc \
					&& lstlast_pars(stack_ops)->type != SUBSH_OPEN)
					push(&stack_ops, &stack_otp);
				lstback_pars(&stack_ops, lstnew_pars(ptr->cmd, \
					ptr->type, ptr->prc));
			}
			else
				lstback_pars(&stack_ops, lstnew_pars(ptr->cmd, ptr->type, ptr->prc));
		}
		ptr = ptr->next;
	}
	while (stack_ops)
		push(&stack_ops, &stack_otp);
	print_types(stack_otp);
	init->pars = NULL;
	//abstract_syntax_tree(init, stack_otp);
}


/*
orig:	ls && cat || ps && (top || head | more | cat)
result:	ls cat && ps || top head more | cat | || &&

ls -l && (pwd || ls) | cat script.sh
ls -l && (pwd || ls) && ls | cat script.sh && pwd || ls
*/

//եթե տեսնում ա && ավտոմատ ձախ ու աջ ա կիսում
//եթե տեսնում ա () ավտոմատ սպասում ա աջինին
//ու վերջնական արժեք պահում, դարձնելով միջինը
//ընդհանուր մի մաս։ Այսինքն իրանից են գնում իրա
//միջի ճյուղավորումները
//այսինքն աջն ու ձախը կլինեն իրա մաս կազմող հրամանի աջն ու ձախը, բայց իրանից ներքև իջնենք մի հատ նոր

//	(ls -l && (ls || pwd)) && (cat script.sh || ls)
//	( && ( || )) && ( || )
//				 ||
//				[&&]
//		 ---------------
//		 ||			  ||
//	(          )    (    )
//	     ||           ||
//	   ------  		 [||]
//   [&&]   ||
//		  (    )
//		   [&&]
/*

այսինքն կարա պրոստը նայի ման գա եթե փակագիծ կա, նախ փակագիծը կառուցի
ոնց ա կառուցելու -» նոր լիստ, որտեղ առաջի տարը կլինի պարենթեզիս
տարրը իրա մեջ կունենա երկրորդ ստրուկտուրա վալուե ու մեջը կպահի փակագծերի մեջ եղածը

հետո ման կգա էլի թազա փակագծեր ճարի, եթե չճարի, ուրեմն ման կգա և

և-ից աջ ու ձախ ընկածները վեկալենք օբշի մի հատ և ստրուկտուրայի մեջ, որ իրա մեջ առանձին կպահի ձախ ու աջ կողմերը
եթե իրանից ձախ կամ աջ փակագխեր կային, նախորդ ստրուկտուրան փակագծերի քցել ևի մեջ
ու տենց շարունակ

left-ով թող արդեն ստեղծածը քցի ուրիշի մեջ, իսկ ռայթով թող քցի իրա մեջ ուրիշին

ասենք


(ls -l || pwd) && cat script.sh | grep echo | wc && ls

ls -l գնաց
հանդիպեց || ու ավելացրեց իրանից ձախ
||	ls -l
գնաց ու հանդիպեց pwd, ավելացրեց իրանից աջ
|| ls -l pwd

ստացանք նման մի բան
cmd:
	||:
		ls -l
		pwd

գնացինք առաջ ու տեսանք փակվող փակագիծը, եղածն ավելացրինք նորի մեջ ձախից, փակագծի
cmd:
	():
		||: (prev, next -> null)
			ls -l (prev null, next -> pwd)
			pwd (prev -> ls -l, next -> null)

գնացինք առաջ ու տեսանք և, ավելացրեցինք ձախից

cmd:
	&&:
		():
			():
				ls -l
				pwd

և-ի աջ կողմը տեսանք cat script.sh, ավելացրինք նեքսթով

cmd:
	&&:
		():
			():
				ls -l
				pwd
		cat script.sh

գնացինք առաջ pipe տեսանք, ավելացրեցինք ձախից

cmd:
	&&:
		():
			():
				ls -l
				pwd
		|:
			cat script.sh

ու տենց մինչև հասանց wc

cmd:
	&&:
		():
			():
				ls -l
				pwd
		|:
			cat script.sh
			grep echo
			wc

*/