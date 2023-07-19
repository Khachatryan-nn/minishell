/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:22:15 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/19 18:51:14 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(t_init *init);

int	static	check_type(t_type type)
{
	if (type == XAND || type == XOR || type == PIPE)
		return (1);
	else if (type == WRITE_APPEND || type == WRITE_TRUNC)
		return (1);
	else if (type == HEREDOC)
		return (1);
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
	return ("");
}

int	is_valid(t_init *init)
{
	//int	i;
	t_lexargs	*ptr;

	ptr = init->lex;
	while (ptr->next != NULL)
	{
		if (check_type(ptr->type) && check_type(ptr->next->type))
		{
			if (check_type(ptr->next->type == HEREDOC))
				return (parse_error(type_is(ptr->type)));
			else
				return (parse_error(type_is(ptr->next->type)));
		}
		ptr = ptr->next;
	}
	return (1);
}
