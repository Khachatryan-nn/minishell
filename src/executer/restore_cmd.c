/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:07:06 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/10 20:08:12 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**alloc_cmd_matrix(char **matrix, char *cmd, t_wcard *wild, int *i);
char	**alloc_wc_matrix(char **matrix, t_tok *stack, t_wcard **wcard);
void	fill_wc_matrix(t_tok *stack, t_wcard **wild);
char	**restore_cmd_line(t_tok *stack, int i);

char	**restore_cmd_line(t_tok *stack, int i)
{
	char	**cmd_matrix;
	int		mode;
	t_tok	*ptr;
	t_wcard	*wcard;

	ptr = stack;
	wcard = (void *)((cmd_matrix = NULL));
	cmd_matrix = alloc_wc_matrix(cmd_matrix, stack, &wcard);
	if (!cmd_matrix)
		return (NULL);
	while (ptr && ptr->cmd)
	{
		mode = (ptr->flag & (_ISCMD_));
		if (mode == 0 && check_type(ptr->type) == 0)
		{
			if (i < 0)
				i++;
			cmd_matrix[i] = ft_strjoin(cmd_matrix[i], ptr->cmd, 1);
		}
		else
			cmd_matrix = alloc_cmd_matrix(cmd_matrix, ptr->cmd, wcard, &i);
		ptr = ptr->next;
	}
	lstclear_wcard(&wcard);
	return (cmd_matrix);
}

char	**alloc_wc_matrix(char **matrix, t_tok *stack, t_wcard **wcard)
{
	int			i;

	i = 0;
	fill_wc_matrix(stack, wcard);
	if (*wcard)
		matrix = (char **)malloc(sizeof(char *) * \
		(lstsize(stack) + lstsize_wcard(*wcard)));
	else
		matrix = (char **)malloc(sizeof(char *) * (lstsize(stack) + 1));
	if (!matrix)
		return (NULL);
	if (*wcard)
		while (i < lstsize(stack) + lstsize_wcard(*wcard) - 1)
			matrix[i++] = NULL;
	else
		while (i < lstsize(stack))
			matrix[i++] = NULL;
	matrix[i] = NULL;
	return (matrix);
}

char	**alloc_cmd_matrix(char **matrix, char *cmd, t_wcard *wild, int *i)
{
	t_wcard	*temp;

	temp = wild;
	if (temp && ft_strchr(cmd, '*'))
	{
		while (temp)
		{
			*i += 1;
			matrix[*i] = ft_strdup(temp->file);
			temp = temp->next;
		}
	}
	else
	{
		*i += 1;
		matrix[*i] = ft_strdup(cmd);
	}
	return (matrix);
}

void	fill_wc_matrix(t_tok *stack, t_wcard **wild)
{
	t_tok	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->type == DQUOTE || tmp->type == SQUOTE)
			tmp = tmp->next;
		else if (ft_strchr(tmp->cmd, '*'))
		{
			get_file(tmp->cmd, wild);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
