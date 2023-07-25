/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:38:30 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 16:39:20 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_parser **res, char *line, int i, int count);
int		handle_wappend(t_parser **res, char *line, int i, int count);
int		handle_wtrunc(t_parser **res, char *line, int i, int count);
int		handle_input(t_parser **res, char *line, int i, int count);

int	handle_heredoc(t_parser **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	lstback(res, lstnew_pars("<<", HEREDOC, 4, 0));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 2);
	}
	return (parse_error("newline"));
}

int	handle_wappend(t_parser **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	lstback(res, lstnew_pars(">>", WRITE_APPEND, 4, 0));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 2);
	}
	return (parse_error("newline"));
}

int	handle_wtrunc(t_parser **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	lstback(res, lstnew_pars(">", WRITE_TRUNC, 4, 0));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 1);
	}
	return (parse_error("newline"));
}

int	handle_input(t_parser **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	lstback(res, lstnew_pars("<", INPUT, 4, 0));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 1);
	}
	return (parse_error("newline"));
}