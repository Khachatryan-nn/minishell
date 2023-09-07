/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:19:28 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 14:04:38 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*token_is(t_type token);
int			is_delimiter(t_tok *root);
const char	*get_token_name(t_type token);

const char	*get_token_name(t_type token)
{
	if (token == WORD)
		return ("WORD");
	else if (token == DQUOTE)
		return ("DQUOTE");
	else if (token == SQUOTE)
		return ("SQUOTE");
	else if (token == SUBSH_OPEN)
		return ("SUBSH_OPEN");
	else if (token == SUBSH_CLOSE)
		return ("SUBSH_CLOSE");
	else if (token == XOR)
		return ("XOR");
	else if (token == XAND)
		return ("XAND");
	else if (token == PIPE)
		return ("PIPE");
	else if (token == HEREDOC)
		return ("HEREDOC");
	else if (token == WR_APPEND)
		return ("WR_APPEND");
	else if (token == WR_TRUNC)
		return ("WR_TRUNC");
	else if (token == END)
		return ("END");
	return ("UNKNOWN");
}

const char	*token_is(t_type token)
{
	if (token == DQUOTE)
		return ("\"");
	else if (token == SQUOTE)
		return ("'");
	else if (token == SUBSH_OPEN)
		return ("(");
	else if (token == SUBSH_CLOSE)
		return (")");
	else if (token == XOR)
		return ("||");
	else if (token == XAND)
		return ("&&");
	else if (token == PIPE)
		return ("|");
	else if (token == HEREDOC)
		return ("<<");
	else if (token == WR_APPEND)
		return (">>");
	else if (token == WR_TRUNC)
		return (">");
	else if (token == INPUT)
		return ("<");
	return ("AST");
}

int	is_delimiter(t_tok *root)
{
	t_tok	*ptr;

	ptr = root;
	if (!ptr)
		return (2);
	ptr = lstlast(ptr);
	if (ptr->type == PIPE || ptr->type == HEREDOC || ptr->type == INPUT)
		return (1);
	else if (ptr->type == XOR || ptr->type == XAND)
		return (1);
	else if (ptr->type == WR_APPEND || ptr->type == WR_TRUNC)
		return (1);
	else if (ptr->type == SUBSH_OPEN || ptr->type == SUBSH_CLOSE)
		return (1);
	else
		return (0);
}
