/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:04:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/17 19:58:15 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_cprnthses(t_parser **res, char *line, int i, int count);
int		handle_prnthses(t_parser **res, char *line, int i, int count);
int		handle_squotes(t_parser **res, char **line, int i, int count);
int		handle_dquotes(t_parser **res, char **line, int i, int count);

int	handle_prnthses(t_parser **res, char *line, int i, int count)
{
	int		counter;
	int		lst;

	lst = 1;
	handle_space(res, line, i, count);
	counter = i;
	lstback(res, lstnew_pars("(", SUBSH_OPEN, 1, 1));
	while (line[counter] && lst)
	{
		counter++;
		if (line[counter] == '(')
			lst++;
		else if (line[counter] == ')')
			lst--;
	}
	if (line[counter] == ')')
		return (1);
	else
		return (0 & parse_error("(", 0));
}

int	handle_cprnthses(t_parser **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	lstback(res, lstnew_pars(")", SUBSH_CLOSE, 1, 0));
	return (i + 1);
}

int	handle_dquotes(t_parser **res, char **line, int i, int count)
{
	int 	val;
	char	*read;
	char	*result;

	handle_space(res, *line, i, count);
	val = add_new_quote(res, *line, i, DQUOTE);
	if ((*line)[val] != '"')
	{
		read = NULL;
	 	result = ft_substr(*line, i + 1, val - i + 1);
	 	while (!read || !ft_strchr(read, '"'))
	 	{
	 		read = readline("dquote> ");
	 		result = strjoin_helper(result, read, 1);
	 	}
		val = add_new_quote(res, result, 0, DQUOTE);
		// printf("--%s--\n", *line);
		*line = ft_strjoin(*line, result, 1);
		// *line = strjoin_helper(*line, result, 1);
		// printf("--%s--\n--%s--\n", *line, result);
		while ((*line)[val] != '"')
			val += 1;
	}
	return (val);
}

int	handle_squotes(t_parser **res, char **line, int i, int count)
{
	int 	val;
	char	*read;
	char	*result;

	handle_space(res, *line, i, count);
	val = add_new_quote(res, *line, i, SQUOTE);
	if ((*line)[val] != '\'')
	{
		read = NULL;
	 	result = ft_substr(*line, i + 1, val - i + 1);
	 	while (!read || !ft_strchr(read, '\''))
	 	{
	 		read = readline("squote> ");
	 		result = strjoin_helper(result, read, 1);
	 	}
		val = add_new_quote(res, result, 0, SQUOTE);
		*line = ft_strjoin(*line, result, 1);
		while ((*line)[val] != '\'')
			val += 1;
	}
	return (val);
}
