/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:04:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/15 17:21:30 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_cprnthses(t_parser **res, char *line, int i, int count);
int		handle_prnthses(t_parser **res, char *line, int i, int count);
int		handle_squotes(t_parser **res, char *line, int i, int count);
int		handle_dquotes(t_parser **res, char *line, int i, int count);

int	handle_prnthses(t_parser **res, char *line, int i, int count)
{
	int		counter;
	int		lst;

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
		return (1);
	else
		return (0 & parse_error("(", 0));
}

int	handle_cprnthses(t_parser **res, char *line, int i, int count)
{
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	lstback(res, lstnew_pars(")", SUBSH_CLOSE, 1, 0));
	return (i + 1);
}

int	handle_dquotes(t_parser **res, char *line, int i, int count)
{
	// int		enable;
	// char	*read;
	// char	*result;
	// int		k;
	// int		counter;
	// char	*str;

	// str = NULL;
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	// if (!add_new_quotes(res, line, i, DQUOTE))
	// {
	// 	enable = 1;
	// 	result = ft_substr(line, i + 1, counter - i + 1);
	// 	if (!result)
	// 		ft_strdup(result);
	// 	while (enable)
	// 	{
	// 		printf("dquote> ");
	// 		read = get_next_line(0);
	// 		if (ft_strchr(read, '"'))
	// 			enable = 0;
	// 		result = strjoin_helper(result, read, 1);
	// 	}
	// 	k = 0;
	// 	while (result[k] && result[k] != '"')
	// 		k++;
	// 	if (is_delitimer(*res))
	// 		lstback(res, lstnew_pars(ft_substr(result, 0, k), DQUOTE, 0, 1));
	// 	else if (i > 1 && line[i - 1])
	// 		lstback(res, lstnew_pars(ft_substr(result, 0, k), DQUOTE, 0, 2));
	// 	else
	// 		lstback(res, lstnew_pars(ft_substr(result, 0, k), DQUOTE, 0, 0));
	// 	if (k < (int) ft_strlen(result))
	// 		lexer(res, result + k + 1);
	// }
	int a = add_new_quote(res, line, i, DQUOTE);
	return (a);
}

int	handle_squotes(t_parser **res, char *line, int i, int count)
{
	// int		counter;
	// int		enable;
	// char	*read;
	// char	*result;
	// int		k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	// if (!add_new_quotes(res, line, i, SQUOTE))
	// {
	// 	enable = 1;
	// 	result = ft_substr(line, i + 1, counter - i - 1);
	// 	if (!result)
	// 		ft_strdup(result);
	// 	while (enable)
	// 	{
	// 		printf("quote> ");
	// 		read = get_next_line(0);
	// 		if (ft_strchr(read, 39))
	// 			enable = 0;
	// 		result = strjoin_helper(result, read, 1);
	// 	}
	// 	k = 0;
	// 	while (result[k] && result[k] != 39)
	// 		k++;
	// 	if (is_delitimer(*res))
	// 		lstback(res, lstnew_pars(ft_substr(result, 0, k), SQUOTE, 0, 1));
	// 	else if (i > 1 && line[i - 1])
	// 		lstback(res, lstnew_pars(ft_substr(result, 0, k), SQUOTE, 0, 2));
	// 	else
	// 		lstback(res, lstnew_pars(ft_substr(result, 0, k), SQUOTE, 0, 0));
	// 	if (k < (int) ft_strlen(result) - 1)
	// 		lexer(res, result + k + 1);
	// }
	int a = add_new_quote(res, line, i, SQUOTE);
	return (a);
}