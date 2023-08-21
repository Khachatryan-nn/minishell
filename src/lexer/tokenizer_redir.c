/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:38:30 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/21 16:30:41 by tikhacha         ###   ########.fr       */
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
	int		k;
	int		start;
	int		end;
	char	*limiter;

	handle_space(res, line, i, count);
	if (is_delimiter(*res))
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars("<<", HEREDOC, 4, 1));
	k = 1;
	start = 0;
	limiter = NULL;
	while ((int)ft_strlen(line) >= i + k && line[i + ++k])
	{
		if (!start && line[i + k] != ' ')
			start = i + k;
		if (start && (line[i + k + 1] == '\0' || line[i + k + 1] == ' '))
		{
			end = i + k;
			limiter = ft_substr(line, start, end - start + 1);
			if (!strncmp(limiter, "&&", 2) || !strncmp(limiter, "||", 2) \
				|| !strncmp(limiter, "<<", 2) || !strncmp(limiter, ">>", 2) )
				return(parse_error(ft_substr(line, start, 2), 1));
			else if (!strncmp(limiter, "&", 1) || !strncmp(limiter, "|", 1) \
				|| !strncmp(limiter, "<", 1) || !strncmp(limiter, ">", 1) )
				return(parse_error(ft_substr(line, start, 1), 1));
			else if (!strncmp(limiter, "&", 1) || !strncmp(limiter, ";", 1))
				return(parse_error(ft_substr(line, start, 1), 1));
			break ;
		}
	}
	if (limiter)
	{
		heredoc_input(limiter, res);
		return (end + 1);
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
		if (line[i + k] != ' ')
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
		if (line[i + k] != ' ')
			return (i + 1);
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
		if (line[i + k] != ' ')
			return (i);
	}
	return (parse_error("newline", 0));
}
