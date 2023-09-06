/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 00:50:41 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/06 23:03:22 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*abstract_syntax_tree(t_init *init, t_tok **stack);
void	print_ast(t_tok *ast, int indent, int lrc);
t_tok	*most_prev(t_tok	*stack);

t_tok	*most_prev(t_tok	*stack)
{
	t_tok	*ptr;

	ptr = stack;
	if (!ptr)
		return (NULL);
	while (ptr && ptr->prev != NULL)
		ptr = ptr->prev;
	return (ptr);
}

void	print_ast(t_tok *ast, int indent, int lrc)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	else if (ast->type == END)
		return (print_ast(ast->right, indent, 0));
	print_ast(ast->right, indent + 1, 1);
	while (i++ < indent)
		printf("\t");
	if (lrc == 0)
		printf("\033[38;5;46m╠══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPES_) && 1, ast->subshell_code);
	else if (lrc == 1)
		printf("\033[38;5;46m╔══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPES_) && 1, ast->subshell_code);
	else if (lrc == 2)
		printf("\033[38;5;46m╚══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPES_) && 1, ast->subshell_code);
	if (ast->next)
		print_ast(ast->next, indent + 1, 2);
	print_ast(ast->left, indent + 1, 2);
}

t_tok	*abstract_syntax_tree(t_init *init, t_tok **stack)
{
	t_tok	*tmp;
	t_tok	*new;

	tmp = lstlast(*stack);
	new = NULL;
	if (!tmp)
		return (NULL);
	else if (tmp->type == END)
	{
		new = ast_branch(tmp);
		pop(stack);
		new->right = most_prev(abstract_syntax_tree(init, stack));
		if (!new)
			return (NULL);
		return (new);
	}
	else if (check_type(tmp->type))
	{
		new = ast_branch(tmp);
		if (tmp->subshell_code)
			new->subshell_code = 1;
		pop(stack);
		new->right = most_prev(abstract_syntax_tree(init, stack));
		new->left = most_prev(abstract_syntax_tree(init, stack));
		if (new && check_type(new->type) == 2)
		{
			if (new->left)
				new->left->flag += _REDIR_;
			if (new->right)
				new->right->flag += _REDIR_;
		}
		return (new);
	}
	else if (tmp && tmp->type != END)
	{
		while (tmp && tmp->cmd && (tmp->flag & 1) == 0)
		{
			push(stack, &init->temp);
			tmp = lstlast(*stack);
		}
		if (tmp && tmp->cmd && (tmp->flag & 1) == 1)
		{
			new = ast_branch(tmp);
			if (tmp->subshell_code)
				new->subshell_code = 1;
			pop(stack);
			while (init && init->temp)
				push(&init->temp, &new);
			return (new);
		}
	}
	return (new);
}
