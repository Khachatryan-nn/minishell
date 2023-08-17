/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:41:52 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/17 17:45:25 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_new_quote(t_parser **res, char *line, int i, int type);
void	heredoc_input(char	*limiter, t_parser **res);

void	heredoc_input(char	*limiter, t_parser **res)
{
	char	*line;
	char	*result;

	line = NULL;
	result = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		if (!result)
			result = line;
		else
			result = strjoin_helper(result, line, 1);
	}
	if (!result)
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	else
		lstback(res, lstnew_pars(result, WORD, 0, 1));
}

int add_new_quote(t_parser **res, char *line, int i, int type)
{
	int		counter;
	char	c;
	char	*str;

	c = '\0';
	if (type == DQUOTE)
		c = '"';
	else if (type == SQUOTE)
		c = '\'';
	counter = i + 1;
	while (line[counter] && line[counter] != c)
		counter++;
	str = ft_substr(line, i + 1, counter - i - 1);
	if (line[counter] == c && is_delimiter(*res))
		lstback(res, lstnew_pars(str, type, 0, 1));
	else if (line[counter] == c && i > 1 && line[i - 1] == ' ')
		lstback(res, lstnew_pars(str, type, 0, 2));
	else if (line[counter] == c)
		lstback(res, lstnew_pars(str, type, 0, 0));
	free(str);
	return (counter);
}
