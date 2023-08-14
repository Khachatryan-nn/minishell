/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_dlms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:39:26 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/14 19:47:15 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(t_parser **res, char *line, int i, int count);
int		handle_pipe(t_parser **res, char *line, int i, int count);
int		handle_xand(t_parser **res, char *line, int i, int count);
int		handle_xor(t_parser **res, char *line, int i, int count);

void	handle_space(t_parser **res, char *line, int i, int count)
{
	char	*str;

	str = NULL;
	if (ft_isspace(line, count, i))
		return ;
	if (is_delitimer(*res))
	{
		str = ft_substr(line, count, i - count);
		lstback(res, lstnew_pars(str, WORD, 0, 3));
	}
	else
	{
		str = ft_substr(line, count, i - count);
		lstback(res, lstnew_pars(str, WORD, 0, 2));
	}
	if (str)
		free(str);
}

int	handle_xor(t_parser **res, char *line, int i, int count)
{
	char *str;

	str = NULL;
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
	{
		str = ft_substr(line, count, i - count);
		lstback(res, lstnew_pars(str, WORD, 0, 1));
	}
	else if (!ft_isspace(line, count, i))
	{
		str = ft_substr(line, count, i - count);
		lstback(res, lstnew_pars(str, WORD, 0, 0));
	}
	if (!(*res))
		return (parse_error("||", 0));
	lstback(res, lstnew_pars("||", XOR, 2, 1));
	if (str)
		free(str);
	return (i + 1);
}

int	handle_xand(t_parser **res, char *line, int i, int count)
{
	char	*str;

	str = NULL;
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
	{
		str = ft_substr(line, count, i - count);
		lstback(res, lstnew_pars(str, WORD, 0, 1));
	}
	else if (!ft_isspace(line, count, i))
	{
		str = ft_substr(line, count, i - count);
		lstback(res, lstnew_pars(str, WORD, 0, 0));
	}
	if (!(*res))
		return (parse_error("&&", 0));
	lstback(res, lstnew_pars("&&", XAND, 2, 1));
	if (str)
		free(str);
	return (i + 1);
}

int	handle_pipe(t_parser **res, char *line, int i, int count)
{
	char	*str;

	str = NULL;
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
	{
		str = ft_substr(line, count, i - count);
		lstback(res, lstnew_pars(str, WORD, 0, 1));
	}
	else if (!ft_isspace(line, count, i))
	{
		str = ft_substr(line, count, i - count);
		lstback(res, lstnew_pars(str, WORD, 0, 0));
	}
	if (!(*res))
		return (parse_error("|", 0));
	lstback(res, lstnew_pars("|", PIPE, 3, 1));
	if (str)
		free(str);
	return (i);
}