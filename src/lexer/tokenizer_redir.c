/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:38:30 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/22 16:47:11 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_parser **res, char *line, int i, int count);
int		handle_wappend(t_parser **res, char *line, int i, int count);
int		handle_wtrunc(t_parser **res, char *line, int i, int count);
int		handle_input(t_parser **res, char *line, int i, int count);

/// @brief 
/// @param res 
/// @param line 
/// @param i 
/// @param count 
/// @return 
int	handle_heredoc(t_parser **res, char *line, int i, int count)
{
	char	*limiter;
	int		end;
	int		start;

	handle_space(res, line, i, count);
	if (is_delimiter(*res))
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars("<<", HEREDOC, 4, 1));
	limiter = NULL;
	start = i + 2;
	while (line[start] && line[start] == ' ')
		start++;
	end = find_limiter_end(line, i, start);
	if (end == 0)
		return (0);
	limiter = ft_substr(line, start, end - start);
	if (limiter)
	{
		heredoc_input(limiter, res);
		return (end);
	}
	return (parse_error("newline", 0));
}

int	handle_wappend(t_parser **res, char *line, int i, int count)
{
	int	k;

	handle_space(res, line, i, count);
	if (is_delimiter(*res))
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars(">>", WRITE_APPEND, 4, 1));
	k = 0;
	while ((int)ft_strlen(line) >= i + k && line[i + ++k])
	{
		if (line[i + k] != ' ' || \
			check_type(token_name(line + i + k)))
			return (i + 1);
	}
	return (parse_error("newline", 0));
}

int	handle_wtrunc(t_parser **res, char *line, int i, int count)
{
	int	k;

	handle_space(res, line, i, count);
	if (is_delimiter(*res))
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars(">", WRITE_TRUNC, 4, 1));
	k = 0;
	while ((int)ft_strlen(line) >= i + k && line[i + ++k])
	{
		if (line[i + k] != ' ' || \
			check_type(token_name(line + i + k)))
			return (i);
	}
	return (parse_error("newline", 0));
}

int	handle_input(t_parser **res, char *line, int i, int count)
{
	int	k;

	handle_space(res, line, i, count);
	if (is_delimiter(*res))
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars("<", INPUT, 4, 1));
	k = 0;
	while ((int)ft_strlen(line) >= i + k && line[i + ++k])
	{
		if (line[i + k] != ' ' || \
			check_type(token_name(line + i + k)))
			return (i);
	}
	return (parse_error("newline", 0));
}
