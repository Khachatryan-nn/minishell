/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:22:15 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/08 00:03:31 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_type(t_type type);
int	is_valid(t_init *init);

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

int	is_valid(t_init *init)
{
	t_tok	*ptr;

	ptr = init->lex;
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
	{
		if (check_type(ptr->type) && check_type(ptr->next->type) == 1)
			return (parse_error(type_is(ptr->next->type), 0));
		else if (check_type(ptr->type) == 2 && \
			!ft_strcmp(ptr->next->cmd, "(NULL)"))
		{
			if (ptr->next->next)
				return (parse_error(type_is(ptr->next->next->type), 0));
		}
		else if (check_type(ptr->type) && ptr->next->type == END)
			return (parse_error("newline", 0));
		ptr = ptr->next;
	}
	return (1);
}
