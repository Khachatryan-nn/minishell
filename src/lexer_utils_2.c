/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:19:28 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/27 18:39:19 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		strjoin_helper(char *read, char *result);
const char* get_token_name(e_type token);

void	strjoin_helper(char *read, char *result)
{
	char	*temp;

	temp = result;
	result = ft_strjoin(temp, "\n");
	free(temp);
	temp = result;
	result = ft_strjoin(temp, read);
	free(read);
	free(temp);
}

const char* get_token_name(e_type token)
{
	if (token == WORD)
		return "WORD";
	if (token == DQUOTE_OPEN)
		return "DQUOTE_OPEN";
	if (token == DQUOTE_CLOSE)
		return "DQUOTE_CLOSE";
	if (token == SQUOTE_OPEN)
		return "SQUOTE_OPEN";
	if (token == SQUOTE_CLOSE)
		return "SQUOTE_CLOSE";
	if (token == SUBSH_OPEN)
		return "SUBSH_OPEN";
	if (token == SUBSH_CLOSE)
		return "SUBSH_CLOSE";
	if (token == MATH_OPEN)
		return "MATH_OPEN";
	if (token == MATH_CLOSE)
		return "MATH_CLOSE";
	if (token == FILEIN)
		return "FILEIN";
	if (token == FILEOUT)
		return "FILEOUT";
	if (token == VAR)
		return "VAR";
	if (token == COMMENT)
		return "COMMENT";
	if (token == CMD)
		return "CMD";
	else
		return "UNKNOWN";
}