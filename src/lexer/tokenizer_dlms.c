/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_dlms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:39:26 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/09 18:43:21 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(t_tok **res, char *line, int i, int count);
int		handle_pipe(t_tok **res, char *line, int i, int count);
int		handle_xand(t_tok **res, char *line, int i, int count);
int		handle_xor(t_tok **res, char *line, int i, int count);

void	handle_space(t_tok **res, char *line, int i, int count)
{
	char	*str;

	str = NULL;
	if (ft_isspace(line, count, i))
		return ;
	str = ft_substr(line, count, i - count);
	if (is_delimiter(*res))
		lstback(res, lstnew_pars(str, WORD, 0, 3));
	else if (count > 1 && line[count - 1] == ' ')
		lstback(res, lstnew_pars(str, WORD, 0, 2));
	else
		lstback(res, lstnew_pars(str, WORD, 0, 0));
	if (str)
		free(str);
}

int	handle_xor(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	if (!(*res))
		return (parse_error("||", 0));
	lstback(res, lstnew_pars("||", XOR, 2, 1));
	return (i + 1);
}

int	handle_xand(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	if (!(*res))
		return (parse_error("&&", 0));
	lstback(res, lstnew_pars("&&", XAND, 2, 1));
	return (i + 1);
}

int	handle_pipe(t_tok **res, char *line, int i, int count)
{
	handle_space(res, line, i, count);
	if (!(*res))
		return (parse_error("|", 0));
	lstback(res, lstnew_pars("|", PIPE, 3, 1));
	return (i);
}
