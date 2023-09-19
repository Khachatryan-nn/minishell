/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:22:15 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/19 20:05:24 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			subshell_validation(t_tok *ptr, int *subshell);
int			is_valid(t_init *init, t_env *env, int *sb);
int			check_type(t_type type);
char static	*type_is(t_type	type);

/// @brief check_type
/// @param type
/// @return 2 if i/o
/// @return 1 etc
int	check_type(t_type type)
{
	if (type == XAND || type == XOR || type == PIPE)
		return (1);
	else if (type == WR_APPEND || type == WR_TRUNC)
		return (2);
	else if (type == HEREDOC || type == INPUT)
		return (2);
	return (0);
}

char static	*type_is(t_type	type)
{
	if (type == XAND)
		return ("&&");
	else if (type == XOR)
		return ("||");
	else if (type == PIPE)
		return ("|");
	else if (type == WR_APPEND)
		return (">>");
	else if (type == WR_TRUNC)
		return (">");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == INPUT)
		return ("<");
	else if (type == END)
		return ("END");
	return ("");
}

int	subshell_validation(t_tok *ptr, int *subshell)
{
	if (ptr->type == SUBSH_OPEN)
		(*subshell)++;
	else if (ptr->type == SUBSH_CLOSE)
		(*subshell)--;
	if (ptr->type == SUBSH_CLOSE && (!ptr->prev || \
		ptr->prev->type == SUBSH_OPEN || (*subshell) < 0))
		return (parse_error(")", 0 + (*subshell = 0)));
	if (ptr->type == SUBSH_CLOSE && ft_strcmp(ptr->next->cmd, "AST") \
		&& ptr->next->type == WORD && ptr->next->type == SQUOTE \
		&& ptr->next->type == DQUOTE)
		return (parse_error(ptr->next->cmd, 0 + (*subshell = 0)));
	if (ptr->type == SUBSH_OPEN && ptr->prev && !check_type(ptr->prev->type))
	{
		if (ptr->next->type != END && ptr->prev->type != SUBSH_OPEN)
			return (parse_error(ptr->next->cmd, 0) + (*subshell = 0));
		else if (ptr->prev->type != SUBSH_OPEN)
			return (parse_error("newline", 0) + (*subshell = 0));
	}
	return (1);
}

int	is_valid(t_init *init, t_env *env, int *sb)
{
	t_tok	*ptr;

	ptr = init->lex;
	while (ptr->next != NULL)
	{
		if (!subshell_validation(ptr, sb))
			return (0);
		if (check_type(ptr->type) == 2 && !ft_strcmp(ptr->next->cmd, "*"))
			return (ft_dprintf(2, "Minishell: *: ambiguous redirect\n"), 0);
		if (ptr->type == HEREDOC && !check_type(ptr->next->type) && \
			ft_strcmp(ptr->next->cmd, "(NULL)"))
			handle_heredoc_input(init, ptr, NULL, env);
		if (check_type(ptr->type) && check_type(ptr->next->type) == 1)
			return (parse_error(type_is(ptr->next->type), 0));
		if (check_type(ptr->type) == 2 && \
			!ft_strcmp(ptr->next->cmd, "(NULL)"))
			if (ptr->next->next)
				return (parse_error(type_is(ptr->next->next->type), 0));
		if (check_type(ptr->type) && ptr->next->type == END)
			return (parse_error("newline", 0));
		if (check_type(ptr->type) == 2 && ptr->type != HEREDOC)
			find_limiter(&ptr->next);
		ptr = ptr->next;
	}
	return (1);
}

// (ls > a) > b