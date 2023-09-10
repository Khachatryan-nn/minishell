/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:38:30 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/11 00:29:15 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc(t_tok **res, char *line, int i, int count);
int		handle_wappend(t_tok **res, char *line, int i, int count);
int		handle_wtrunc(t_tok **res, char *line, int i, int count);
int		handle_input(t_tok **res, char *line, int i, int count);

/// @brief 
/// @param res 
/// @param line 
/// @param i 
/// @param count 
/// @return 
int	handle_heredoc(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	if (is_delimiter(*res) && is_delimiter(*res) != 3)
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars("<<", HEREDOC, 4, 1));
	return (i + 1);
}

int	handle_wappend(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	if (is_delimiter(*res) && is_delimiter(*res) != 3)
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars(">>", WR_APPEND, 4, 1));
	return (i + 1);
}

int	handle_wtrunc(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	if (is_delimiter(*res) && is_delimiter(*res) != 3)
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars(">", WR_TRUNC, 4, 1));
	return (i);
}

int	handle_input(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	if (is_delimiter(*res) && is_delimiter(*res) != 3)
		lstback(res, lstnew_pars("(NULL)", WORD, 0, 1));
	lstback(res, lstnew_pars("<", INPUT, 4, 1));
	return (i);
}
