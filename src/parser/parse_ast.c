/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 00:50:41 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/22 01:32:10 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*abstract_syntax_tree(t_init *init, t_parser **stack);
void		print_ast(t_parser *ast, int indent, int lrc);

t_parser	*most_prev(t_parser	*stack)
{
	t_parser	*ptr;

	ptr = stack;
	if (!ptr)
		return (NULL);
	while (ptr && ptr->prev != NULL)
		ptr = ptr->prev;
	return (ptr);
}

void	print_ast(t_parser *ast, int indent, int lrc)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	else if (ast->type == END)
	{
		print_ast(ast->right, indent, 0);
		return ;
	}
	print_ast(ast->right, indent + 1, 1);
	while (i++ < indent)
	{
		printf("\t");
	}
	if (lrc == 0)
		printf("\033[38;5;46m╠══════\033[0m[%s][%d][%d]\n", ast->cmd, (ast->flag & _PIPES_) && 1, ast->subshell_code);
	else if (lrc == 1)
		printf("\033[38;5;46m╔══════\033[0m[%s][%d][%d]\n", ast->cmd, (ast->flag & _PIPES_) && 1, ast->subshell_code);
	else if (lrc == 2)
		printf("\033[38;5;46m╚══════\033[0m[%s][%d][%d]\n", ast->cmd, (ast->flag & _PIPES_) && 1, ast->subshell_code);
	if (ast->next)
		print_ast(ast->next, indent + 1, 2);
	print_ast(ast->left, indent + 1, 2);
}

t_parser	*abstract_syntax_tree(t_init *init, t_parser **stack)
{
	t_parser	*ptr;
	t_parser	*new;

	new = NULL;
	ptr = lstlast(*stack);
	if (!ptr)
		return (NULL);
	if (ptr->type == END)
	{
		new = lstnew_pars(ptr->cmd, ptr->type, ptr->prc, ptr->flag);
		pop(stack);
		new->right = most_prev(abstract_syntax_tree(init, stack));
		if (!new)
			return (NULL);
		return (new);
	}
	else if (check_type(ptr->type))
	{
		new = lstnew_pars(ptr->cmd, ptr->type, ptr->prc, ptr->flag);
		if (ptr->subshell_code)
			new->subshell_code = 1;
		pop(stack);
		new->right = most_prev(abstract_syntax_tree(init, stack));
		new->left = most_prev(abstract_syntax_tree(init, stack));
		// if (new->left)
		if (new && check_type(new->type) == 2)
		{
			if (new->left)
			{
				new->left->flag += _REDIR_;
				if (new->left->cmd)
					new->lpath = new->left->cmd;
			}
			if (new->right)
			{
				new->right->flag += _REDIR_;
				if (new->right->cmd)
					new->rpath = new->right->cmd;
			}
		}
		return (new);
	}
	else if (ptr && ptr->type != END)
	{
		while (ptr && ptr->cmd && (ptr->flag & 1) == 0)
		{
			push(stack, &init->temp);
			ptr = lstlast(*stack);
		}
		if (ptr && ptr->cmd && (ptr->flag & 1) == 1)
		{
			new = lstnew_pars(ptr->cmd, ptr->type, ptr->prc, ptr->flag);
			if (ptr->subshell_code)
				new->subshell_code = 1;
			pop(stack);
			while (init && init->temp)
				push(&init->temp, &new);
			return (new);
		}
	}
	return (new);
}
