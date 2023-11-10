/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:45:02 by tikhacha          #+#    #+#             */
/*   Updated: 2023/11/10 15:29:02 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_implementation(t_tok **tmp, t_tok **cmd_l);
int		parse_error(char *err_str, int mode);
void	print_types(t_tok *ptr);
int		is_wrd(t_tok *tok);

int	parse_error(char *err_str, int mode)
{
	if (err_str[0] == '(' || err_str[0] == '\'' || err_str[0] == '"')
		ft_dprintf(2, "minishell: syntax error missing token `%s'\n", err_str);
	else
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n", \
		err_str);
	if (mode)
		free (err_str);
	return (0);
}

void	print_types(t_tok *ptr)
{
	if (!ptr)
		printf("%p", NULL);
	while (ptr)
	{
		if (ptr->next != NULL)
			printf("%s [%d] ", ptr->cmd, ptr->flag & (_SUBSH_));
		else
			printf("%s [%d]", ptr->cmd, ptr->flag & (_SUBSH_));
		ptr = ptr->next;
	}
	printf("\n");
}

void	if_implementation(t_tok **tmp, t_tok **cmd_l)
{
	while ((*tmp) && (*tmp)->next && ((*tmp)->type == WORD || \
		(*tmp)->type == SQUOTE || (*tmp)->type == DQUOTE) && \
		(*tmp)->next->type != END && check_type((*tmp)->next->type) <= 0 && \
		(*tmp)->next->type != SUBSH_CLOSE)
		(*tmp) = (*tmp)->next;
	while (((*tmp)->type == WORD || (*tmp)->type == SQUOTE || \
					(*tmp)->type == DQUOTE) && (*tmp)->prev && \
		check_type((*tmp)->prev->type) != 2 && (*tmp)->prev->type != SUBSH_OPEN)
	{
		(*tmp) = (*tmp)->prev;
		push_redir(*cmd_l, (*tmp)->next);
	}
}

/// @brief
/// @param tok 
/// @return word: 1, squote:2, dquote:3, other:0
int	is_wrd(t_tok *tok)
{
	if (tok == NULL)
		return (0);
	if (tok->type == WORD)
		return (1);
	else if (tok->type == SQUOTE)
		return (2);
	else if (tok->type == DQUOTE)
		return (3);
	else
		return (0);
}
