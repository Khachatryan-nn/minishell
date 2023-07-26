/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:19:28 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/26 19:14:01 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*get_token_name(t_type token);
int			is_delitimer(t_parser *root);

const char* get_token_name(t_type token)
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
	else if (token == WRITE_APPEND)
		return ("WRITE_APPEND");
	else if (token == WRITE_TRUNC)
		return ("WRITE_TRUNC");
	else if (token == FILEIN)
		return ("FILEIN");
	else if (token == FILEOUT)
		return ("FILEOUT");
	else if (token == END)
		return ("END");
	else
		return ("UNKNOWN");
}

int	is_delitimer(t_parser *root)
{
	t_parser	*ptr;

	ptr = root;
	if (!ptr)
		return (2);
	ptr = lstlast(ptr);
	if (ptr->type == PIPE || ptr->type == HEREDOC)
		return (1);
	else if (ptr->type == XOR || ptr->type == XAND)
		return (1);
	else if (ptr->type == WRITE_APPEND || ptr->type == WRITE_TRUNC)
		return (1);
	else if (ptr->type == SUBSH_OPEN || ptr->type == SUBSH_CLOSE)
		return (1);
	else
		return (0);
}