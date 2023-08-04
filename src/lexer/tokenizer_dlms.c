/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_dlms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:39:26 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/04 16:49:02 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(t_parser **res, char *line, int i, int count);
int		handle_pipe(t_parser **res, char *line, int i, int count);
int		handle_xand(t_parser **res, char *line, int i, int count);
int		handle_xor(t_parser **res, char *line, int i, int count);

void	handle_space(t_parser **res, char *line, int i, int count)
{
	if (ft_isspace(line, count, i))
		return ;
	if (is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 3));
	else
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 2));
}

int	handle_xor(t_parser **res, char *line, int i, int count)
{
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	if (!(*res))
		return (parse_error("||"));
	lstback(res, lstnew_pars("||", XOR, 2, 1));
	return (i + 1);
}

int	handle_xand(t_parser **res, char *line, int i, int count)
{
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	if (!(*res))
		return (parse_error("&&"));
	lstback(res, lstnew_pars("&&", XAND, 2, 1));
	return (i + 1);
}

int	handle_pipe(t_parser **res, char *line, int i, int count)
{
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 1));
	else if (!ft_isspace(line, count, i))
		lstback(res, lstnew_pars(ft_substr(line, count, i - count), WORD, 0, 0));
	if (!(*res))
		return (parse_error("|"));
	lstback(res, lstnew_pars("|", PIPE, 3, 1));
	return (i);
}
