/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:04:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/29 17:34:56 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_prnthses(t_lexargs **res, char *line, int i, int count);
int		handle_squotes(t_lexargs **res, char *line, int i, int count);
int		handle_dquotes(t_lexargs **res, char *line, int i, int count);
int		handle_heredoc(t_lexargs **res, char *line, int i, int count);
void	handle_space(t_lexargs **res, char *line, int i, int count);
int		handle_pipe(t_lexargs **res, char *line, int i, int count);
int		handle_xand(t_lexargs **res, char *line, int i, int count);
int		handle_and(t_lexargs **res, char *line, int i, int count);
int		handle_xor(t_lexargs **res, char *line, int i, int count);

void	handle_space(t_lexargs **res, char *line, int i, int count)
{
	if (ft_isspace(line, i, count))
		return ;
	ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
}

int	handle_prnthses(t_lexargs **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		k;

	if (!ft_isspace(line, i, count))
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
	counter = i + 1;
	ft_lstadd_back_3(res, ft_lstnew_3("(", SUBSH_OPEN));
	while (line[counter] != ')' && line[counter])
		counter++;
	if (line[counter] == ')')
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, i + 1, counter - i - 1), WORD));
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i - 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("subsh> ");
			if (ft_strchr(read, ')'))
				enable = 0;
			strjoin_helper(result, read);
		}
		k = 0;
		while (result[k] && result[k] != ')')
			k++;
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(result, 0, k), WORD));
		if (k < (int) ft_strlen(result))
			lexer(res, result + k + 1);
	}
	ft_lstadd_back_3(res, ft_lstnew_3(")", SUBSH_CLOSE));
	return (counter);
}

int	handle_dquotes(t_lexargs **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		k;

	if (!ft_isspace(line, i, count))
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
	counter = i + 1;
	ft_lstadd_back_3(res, ft_lstnew_3("\"", DQUOTE_OPEN));
	while (line[counter] != '"' && line[counter])
		counter++;
	if (line[counter] == '"')
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, i + 1, counter - i - 1), WORD));
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i - 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("dquote> ");
			if (ft_strchr(read, '"'))
				enable = 0;
			strjoin_helper(result, read);
		}
		k = 0;
		while (result[k] && result[k] != '"')
			k++;
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(result, 0, k), WORD));
		if (k < (int) ft_strlen(result))
			lexer(res, result + k + 1);
	}
	ft_lstadd_back_3(res, ft_lstnew_3("\"", DQUOTE_CLOSE));
	return (counter);
}

int	handle_squotes(t_lexargs **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		k;

	if (!ft_isspace(line, i, count))
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
	counter = i + 1;
	ft_lstadd_back_3(res, ft_lstnew_3("'", SQUOTE_OPEN));
	while (line[counter] != 39 && line[counter])
		counter++;
	if (line[counter] == 39)
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, i + 1, counter - i - 1), WORD));
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i - 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("quote> ");
			if (ft_strchr(read, 39))
				enable = 0;
			strjoin_helper(result, read);
		}
		k = 0;
		while (result[k] && result[k] != 39)
			k++;
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(result, 0, k), WORD));
		if (k < (int) ft_strlen(result) - 1)
			lexer(res, result + k + 1);
	}
	ft_lstadd_back_3(res, ft_lstnew_3("'", SQUOTE_CLOSE));
	return (counter);
}

int	handle_xor(t_lexargs **res, char *line, int i, int count)
{
	if (!ft_isspace(line, i, count))
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
	ft_lstadd_back_3(res, ft_lstnew_3("||", XOR));
	return (i + 1);
}

int	handle_xand(t_lexargs **res, char *line, int i, int count)
{
	if (!ft_isspace(line, i, count))
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
	ft_lstadd_back_3(res, ft_lstnew_3("&&", XAND));
	return (i + 1);
}

int	handle_pipe(t_lexargs **res, char *line, int i, int count)
{
	if (!ft_isspace(line, i, count))
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
	ft_lstadd_back_3(res, ft_lstnew_3("|", PIPE));
	return (i + 1);
}

int	handle_and(t_lexargs **res, char *line, int i, int count)
{
	if (!ft_isspace(line, i, count))
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
	ft_lstadd_back_3(res, ft_lstnew_3("&", AND));
	return (i + 1);
}

int	static	parse_error(void)
{
	write (1, "minishell: syntax error near unexpected token `newline'\n", 56);
	return (1);
}

int	handle_heredoc(t_lexargs **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, i, count))
		ft_lstadd_back_3(res, ft_lstnew_3(ft_substr(line, count, i - count), WORD));
	ft_lstadd_back_3(res, ft_lstnew_3("<<", HEREDOC));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 1);
	}
	return (parse_error());
}
