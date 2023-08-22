/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:07:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/22 14:35:32 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	token_name(char *token);
int		ft_isspace(char *line, int i, int j);

//Checks if there only spaces from i -> j.\
//If there are only spaces returns 1.
int	ft_isspace(char *line, int i, int j)
{
	while (i < j && line[i])
	{
		if (line[i] != ' ' && line[i] != '	')
			return (0);
		i++;
	}
	return (1);
}

t_type	token_name(char *token)
{
	if (token[0] == '"')
		return (DQUOTE);
	else if (token[0] == '\'')
		return (SQUOTE);
	else if (token[0] == '(')
		return (SUBSH_OPEN);
	else if (token[0] == ')')
		return (SUBSH_CLOSE);
	else if (token[0] == '|' && token[1] == '|')
		return (XOR);
	else if (token[0] == '&' && token[1] == '&')
		return (XAND);
	else if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '<' && token[1] == '<')
		return (HEREDOC);
	else if (token[0] == '>' && token[1] == '>')
		return (WRITE_APPEND);
	else if (token[0] == '>')
		return (WRITE_TRUNC);
	else if (token[0] == '<')
		return (INPUT);
	else if (token[0] == '\0')
		return (END);
	return (WORD);
}
