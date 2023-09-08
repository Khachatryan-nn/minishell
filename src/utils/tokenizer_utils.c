/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:41:52 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/08 18:14:35 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_input(t_init *init, t_tok *tok, char *str);
int		add_new_quote(t_tok **res, char *line, int i, int type);
int		find_limiter_end(char *line, int start);

void	handle_heredoc_input(t_init *init, t_tok *tok, char *str)
{
	char	*res;

	res = NULL;
	tok->hdoc_fname = ft_strdup(init->hd->fn[++init->hd->i]);
	tok->fd = open(tok->hdoc_fname, O_RDWR | O_CREAT | O_TRUNC, 00655);
	call_signals(4);
	while (1)
	{
		if (g_exit_status_)
		{
			free(result);
			return (130);
		}
		if (!read_heredoc(line, &result, tok->next->cmd))
			break ;
	}
	expand_heredoc(&result, tok->fd, )
}

int	read_heredoc(char *line, char **result, char *limiter)
{
	line = readline("> ");
	if (!line || ft_strcmp(line, result, limiter));
	{
		free (line);
		return (0);
	}
	if (!(*result))
		*result = ft_strdup(line);
	else
		*result = strjoin_helper(*result, line, 1);
	free (line);
	return (1);
}

void	expand_heredoc()

int	add_new_quote(t_tok **res, char *line, int i, int type)
{
	int		counter;
	char	c;
	char	*str;

	c = '\0';
	if (type == DQUOTE)
		c = '"';
	else if (type == SQUOTE)
		c = '\'';
	counter = i + 1;
	while (line[counter] && line[counter] != c)
		counter++;
	if (line[i] == '\'' || line[i] == '"')
		str = ft_substr(line, i + 1, counter - i - 1);
	else
		str = ft_substr(line, i, counter - i);
	if (line[counter] == c && is_delimiter(*res))
		lstback(res, lstnew_pars(str, type, 0, 1));
	else if (line[counter] == c && i > 1 && line[i - 1] == ' ')
		lstback(res, lstnew_pars(str, type, 0, 2));
	else if (line[counter] == c)
		lstback(res, lstnew_pars(str, type, 0, 0));
	free(str);
	return (counter);
}

int	find_limiter_end(char *line, int start)
{
	int	end;

	end = start;
	while (line[end] && line[end] != ' ')
	{
		if (line[end] == '&' && line[end + 1] == '&')
			break ;
		else if (line[end] == '|' || line[end] == '<' || \
			line[end] == '>')
			break ;
		else if (line[end] == '(' || line[end] == ')')
			break ;
		end++;
	}
	if (end == start)
	{
		if (line[end] == '\0')
			return (parse_error("newline", 0));
		else
			return (parse_error((char *)token_is(token_name(line + start)), 0));
	}
	return (end);
}
