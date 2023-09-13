/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:07:04 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/13 22:25:18 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ast(t_init *init, t_tok *root, t_env *env);
int	andor_check(t_tok *stack);

int	andor_check(t_tok *stack)
{
	if (stack->type == XAND && stack->left && stack->left->err_code != 0)
	{
		stack->err_code = stack->left->err_code;
		return (0);
	}
	else if (stack->type == XOR && stack->left && stack->left->err_code == 0)
	{
		stack->err_code = stack->left->err_code;
		return (0);
	}
	else
		return (1);
}

int	check_ast(t_init *init, t_tok *root, t_env *env)
{
	int		status;

	status = 0;
	if (!root)
	{
		root->err_code = 258;
		return (root->err_code);
	}
	if (root->left == NULL && root->right == NULL)
	{
		root->err_code = to_execute(init, root, env);
		return (root->err_code);
	}
	if (root->left && root->right && check_type(root->type) == 2)
		root->err_code = exec_iocmd(init, root, env);
	else if (root->left && root->right && root->type == PIPE)
	{
		config_right_dups(root);
		root->err_code = pipe_prepair(init, root, env);
	}
	if (root->left != NULL && !(root->left->flag & (_REDIR_)) && \
		!(root->left->flag & (_PIPES_)))
		root->err_code = left_branch(init, root, env, status);
	if (root->right != NULL && andor_check(root) && \
		!(root->right->flag & (_REDIR_)) && !(root->right->flag & (_PIPES_)))
		root->err_code = right_branch(init, root, env, status);
	handle_dollar(root->err_code, env);
	return (root->err_code);
}
