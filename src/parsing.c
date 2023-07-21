/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:19:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/21 18:03:40 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_list *env, t_init *init);

void	parser(t_list *env, t_init *init)
{
	//char		*str;
	//t_lexargs	*ptr;
	//t_parser	*pars_ptr;
	//t_parser	*stack_ops;
	//int			flag;

	//flag = 0;
	//str = NULL;
	(void)	env;
	init->pars = NULL;
}


/*
ls && cat script.sh
ls -> cmd
parser (ls as head)
&& -> xand -> && -> left ls -> right null
parser (&& as head)
cat script.sh -> && 

*/









	//while (init->lex != NULL)
	//{
	//	if (restore_cmd_line(init->lex, &str))
	//	{
	//		ptr = init->lex;
	//		init->lex = init->lex->next;
	//		if (init->lex != NULL)
	//			continue ;
	//	}
	//	else if (init->lex->type == PIPE && flag == 0)
	//	{
	//		lstadd_back_pars(&init->pars, lstnew_pars(str, ptr->type));
	//		pars_ptr = init->pars;
	//		init->pars = lstnew_pars("|", PIPE);
	//		init->pars->left = pars_ptr;
	//		flag = 1;
	//	}
	//	else if (flag == 1)
	//		init->pars->right = lstnew_pars(str, ptr->type);
	//	else
	//		lstadd_back_pars(&init->pars, lstnew_pars(str, ptr->type));
	//	if (init->lex && init->lex->next)
	//		init->lex = init->lex->next;
	//	print_types(init);
	//	//printf("%p\n", ptr->next);



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