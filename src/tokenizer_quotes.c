/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:04:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 15:46:51 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_prnthses(t_parser **res, char *line, int i, int count);
int		handle_squotes(t_parser **res, char *line, int i, int count);
int		handle_dquotes(t_parser **res, char *line, int i, int count);

int	handle_prnthses(t_parser **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		lst;
	int		k;

	lst = 1;
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
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
	{
		line[counter] = '\0';
		lexer(res, line + i + 1);
		line[counter] = ')';
	}
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i - 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("subsh> ");
			if (ft_strchr(read, ')'))
				enable = 0;
			result = strjoin_helper(result, read, 1);
		}
		k = 0;
		while (result[k] && result[k] != ')')
			k++;
		lexer(res, ft_substr(result, 0, k));
		if (k < (int) ft_strlen(result))
			lexer(res, result + k + 1);
	}
	lstback(res, lstnew_pars(")", SUBSH_CLOSE, 1, 1));
	return (counter);
}

int	handle_dquotes(t_parser **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	counter = i + 1;
	while (line[counter] != '"' && line[counter])
		counter++;
	if (line[counter] == '"' && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, i + 1, counter - i - 1), DQUOTE, 0, 1));
	else if (line[counter] == '"' && i > 1 && line[i - 1] == ' ')
		lstback(res, lstnew_pars(ft_substr(line, i + 1, counter - i - 1), DQUOTE, 0, 2));
	else if (line[counter] == '"')
		lstback(res, lstnew_pars(ft_substr(line, i + 1, counter - i - 1), DQUOTE, 0, 0));
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i + 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("dquote> ");
			if (ft_strchr(read, '"'))
				enable = 0;
			result = strjoin_helper(result, read, 1);
		}
		k = 0;
		while (result[k] && result[k] != '"')
			k++;
		if (is_delitimer(*res))
			lstback(res, lstnew_pars(ft_substr(result, 0, k), DQUOTE, 0, 1));
		else if (i > 1 && line[i - 1])
			lstback(res, lstnew_pars(ft_substr(result, 0, k), DQUOTE, 0, 2));
		else
			lstback(res, lstnew_pars(ft_substr(result, 0, k), DQUOTE, 0, 0));
		if (k < (int) ft_strlen(result))
			lexer(res, result + k + 1);
	}
	return (counter);
}

int	handle_squotes(t_parser **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	counter = i + 1;
	while (line[counter] != 39 && line[counter])
		counter++;
	if (line[counter] == 39 && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, i + 1, counter - i - 1), SQUOTE, 3, 1));
	else if (line[counter] == 39 && i > 1 && line[i - 1])
		lstback(res, lstnew_pars(ft_substr(line, i + 1, counter - i - 1), SQUOTE, 0, 2));
	else if (line[counter] == 39)
		lstback(res, lstnew_pars(ft_substr(line, i + 1, counter - i - 1), SQUOTE, 0, 0));
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i - 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("quote> ");
			if (ft_strchr(read, 39))
				enable = 0;
			result = strjoin_helper(result, read, 1);
		}
		k = 0;
		while (result[k] && result[k] != 39)
			k++;
		if (is_delitimer(*res))
			lstback(res, lstnew_pars(ft_substr(result, 0, k), SQUOTE, 0, 1));
		else if (i > 1 && line[i - 1])
			lstback(res, lstnew_pars(ft_substr(result, 0, k), SQUOTE, 0, 2));
		else
			lstback(res, lstnew_pars(ft_substr(result, 0, k), SQUOTE, 0, 0));
		if (k < (int) ft_strlen(result) - 1)
			lexer(res, result + k + 1);
	}
	return (counter);
}
