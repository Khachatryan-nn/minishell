/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:04:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/10 19:58:21 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_cprnthses(t_tok **res, char *line, int i, int count);
char	*handle_quotes(t_tok **res, char **line, int *i, int count);
int		handle_squotes(t_tok **res, char **line, int *i, int count);
int		handle_dquotes(t_tok **res, char **line, int *i, int count);
int		handle_prnthses(t_tok **res, char *line, int i, int count);

int	handle_prnthses(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	lstback(res, lstnew_pars("(", SUBSH_OPEN, 1, 1));
	return (i);
}

int	handle_cprnthses(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	lstback(res, lstnew_pars(")", SUBSH_CLOSE, 1, 0));
	return (i);
}

int	handle_dquotes(t_tok **res, char **line, int *i, int count)
{
	int		val;
	char	*read;
	char	*result;

	handle_space(res, *line, *i, count);
	val = add_new_quote(res, *line, *i, DQUOTE);
	if ((*line)[val] != '"')
	{
		read = NULL;
		result = ft_substr(*line, *i + 1, val - *i + 1);
		while (!read || !ft_strchr(result, '"'))
		{
			read = readline("dquote> ");
			if (read == NULL)
				return (-42);
			result = strjoin_helper(result, read, 1);
			free (read);
		}
		val = add_new_quote(res, result, 0, DQUOTE);
		*line = ft_strjoin(*line, result, 1);
		free(result);
		while ((*line)[val] != '"')
			val++;
	}
	return (*i = val);
}

int	handle_squotes(t_tok **res, char **line, int *i, int count)
{
	int		val;
	char	*read;
	char	*result;

	handle_space(res, *line, *i, count);
	val = add_new_quote(res, *line, *i, SQUOTE);
	if ((*line)[val] != '\'')
	{
		read = NULL;
		result = ft_substr(*line, *i + 1, val - *i + 1);
		while (!read || !ft_strchr(result, '\''))
		{
			read = readline("squote> ");
			if (read == NULL)
				return (-42);
			result = strjoin_helper(result, read, 1);
			free (read);
		}
		val = add_new_quote(res, result, 0, SQUOTE);
		*line = ft_strjoin(*line, result, 1);
		free(result);
		while ((*line)[val] != '\'')
			val++;
	}
	return (*i = val);
}

char	*handle_quotes(t_tok **res, char **line, int *i, int count)
{
	int	status;

	if ((*line)[*i] == '\'')
	{
		status = handle_squotes(res, line, i, count);
		if (status < 0)
			return ("\'");
	}
	if ((*line)[*i] == '\"')
	{
		status = handle_dquotes(res, line, i, count);
		if (status < 0)
			return ("\"");
	}
	return (NULL);
}
