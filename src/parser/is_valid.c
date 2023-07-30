/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:22:15 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/30 20:38:25 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_type(t_type type);
int	is_valid(t_init *init);

int	check_type(t_type type)
{
	if (type == XAND || type == XOR || type == PIPE)
		return (1);
	else if (type == WRITE_APPEND || type == WRITE_TRUNC)
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
	else if (type == WRITE_APPEND)
		return (">>");
	else if (type == WRITE_TRUNC)
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
	t_parser	*ptr;

	ptr = init->lex;
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
	{
		if (check_type(ptr->type) && check_type(ptr->next->type) == 1)
		{
			//if (ptr->next->type == HEREDOC))
			//	return (parse_error(type_is(ptr->type)));
			//else
				return (parse_error(type_is(ptr->next->type)));
		}
		else if (check_type(ptr->type) && ptr->next->type == END)
			return (parse_error("newline"));
		ptr = ptr->next;
	}
	return (1);
}
