/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 00:50:41 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/26 16:23:31 by tikhacha         ###   ########.fr       */
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
		printf("\033[38;5;46m╠══════\033[0m[%s][%d]\n", ast->cmd, (ast->flag & 1 << 1) && 1);
	else if (lrc == 1)
		printf("\033[38;5;46m╔══════\033[0m[%s][%d]\n", ast->cmd, (ast->flag & 1 << 1) && 1);
	else if (lrc == 2)
		printf("\033[38;5;46m╚══════\033[0m[%s][%d]\n", ast->cmd, (ast->flag & 1 << 1) && 1);
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
		return (new);
	}
	if (ptr->type == XOR || ptr->type == XAND || ptr->type == PIPE || \
		ptr->type == HEREDOC || ptr->type == INPUT || ptr->type == WRITE_APPEND \
		|| ptr->type == WRITE_TRUNC)
	{
		new = lstnew_pars(ptr->cmd, ptr->type, ptr->prc, ptr->flag);
		pop(stack);
		new->right = most_prev(abstract_syntax_tree(init, stack));
		new->left = most_prev(abstract_syntax_tree(init, stack));
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
			pop(stack);
			while (init && init->temp)
				push(&init->temp, &new);
			return (new);
		}
	}
	return (new);
}
