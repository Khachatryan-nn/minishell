/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:41:52 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/23 18:57:10 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_new_quote(t_parser **res, char *line, int i, int type);
int		find_limiter_end(char *line, int i, int start);
void	heredoc_input(char	*limiter, t_parser **res);

void	heredoc_input(char	*limiter, t_parser **res)
{
	char	*line;
	char	*result;

	line = NULL;
	result = NULL;
	close((*res)->pipes[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		if (!result)
			result = line;
		else
			result = strjoin_helper(result, line, 1);
	}
	if (!result)
		result = ft_strdup("");
	else
		result = ft_strjoin(result, "\n", 1);
	if (dup2((*res)->pipes[1], STDOUT_FILENO) < 0)
	{
		perror("minishell");
		exit(_close_((*res)->pipes[1]));
	}
	write((*res)->pipes[1], result, ft_strlen(result));
	_close_((*res)->pipes[1]);
}

int	add_new_quote(t_parser **res, char *line, int i, int type)
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

int	find_limiter_end(char *line, int i, int start)
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
		if (line[i] == '\0')
			return (parse_error("newline", 1));
		else
			return (parse_error((char *)token_is(token_name(line + start)), 0));
	}
	return (end);
}
