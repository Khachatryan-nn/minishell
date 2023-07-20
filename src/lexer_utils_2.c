/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:19:28 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/19 17:32:16 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		strjoin_helper(char *read, char *result);
const char* get_token_name(t_type token);

void	strjoin_helper(char *read, char *result)
{
	char	*temp;

	temp = result;
	result = ft_strjoin(temp, "\n");
	free(temp);
	temp = 0;
	temp = result;
	result = ft_strjoin(temp, read);
	if (temp)
		free(temp);
	temp = 0;
}

const char* get_token_name(t_type token)
{
	if (token == WORD)
		return ("WORD");
	else if (token == DQUOTE_OPEN)
		return ("DQUOTE_OPEN");
	else if (token == DQUOTE_CLOSE)
		return ("DQUOTE_CLOSE");
	else if (token == SQUOTE_OPEN)
		return ("SQUOTE_OPEN");
	else if (token == SQUOTE_CLOSE)
		return ("SQUOTE_CLOSE");
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