/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:04:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/24 20:16:06 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_prnthses(t_lexargs **res, char *line, int i, int count);
int		handle_squotes(t_lexargs **res, char *line, int i, int count);
int		handle_dquotes(t_lexargs **res, char *line, int i, int count);
int		handle_heredoc(t_lexargs **res, char *line, int i, int count);
int		handle_wappend(t_lexargs **res, char *line, int i, int count);
int		handle_wtrunc(t_lexargs **res, char *line, int i, int count);
int		handle_input(t_lexargs **res, char *line, int i, int count);
void	handle_space(t_lexargs **res, char *line, int i, int count);
int		handle_pipe(t_lexargs **res, char *line, int i, int count);
int		handle_xand(t_lexargs **res, char *line, int i, int count);
int		handle_xor(t_lexargs **res, char *line, int i, int count);

void	handle_space(t_lexargs **res, char *line, int i, int count)
{
	if (ft_isspace(line, count, i))
		return ;
	//printf("line to check is %s\n", line + count);
	if (is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
}

int	handle_prnthses(t_lexargs **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else if (!ft_isspace(line, count, i))
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	counter = i + 1;
	lstback_lex(res, lstnew_lex("(", SUBSH_OPEN, 1));
	while (line[counter] && line[counter] != ')')
		counter++;
	if (line[counter] == ')')
	{
		line[counter] = '\0';
		lexer(res, line + i + 1);
		line[counter] = ')';
	}
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
			result = strjoin_helper(result, read, 1);
		}
		k = 0;
		while (result[k] && result[k] != ')')
			k++;
		lexer(res, ft_substr(result, 0, k));
		if (k < (int) ft_strlen(result))
			lexer(res, result + k + 1);
	}
	lstback_lex(res, lstnew_lex(")", SUBSH_CLOSE, 1));
	return (counter);
}

int	handle_dquotes(t_lexargs **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	// if (!ft_isspace(line, count, i) && is_delitimer(*res))
	// 	lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	// else if (!ft_isspace(line, count, i))
	// 	strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	counter = i + 1;
	while (line[counter] != '"' && line[counter])
		counter++;
	if (line[counter] == '"')
		lstback_lex(res, lstnew_lex(ft_substr(line, i + 1, counter - i - 1), DQUOTE, 0));
	// if (line[counter] == '"' && is_delitimer(*res))
	// 	lstback_lex(res, lstnew_lex(ft_substr(line, i + 1, counter - i - 1), DQUOTE, 0));
	// else if (line[counter])
	// 	lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, i - 1, counter - i + 1), 2);
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i + 1);
		// result = ft_substr(line, i - 1, counter - i + 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("dquote> ");
			if (ft_strchr(read, '"'))
				enable = 0;
			result = strjoin_helper(result, read, 1);
		}
		k = 0;
		// if (i == 0)
		// 	k = 1;
		// else
		// 	k = 2;
		while (result[k] && result[k] != '"')
			k++;
		lstback_lex(res, lstnew_lex(ft_substr(result, 0, k), DQUOTE, 0));
		// if (is_delitimer(*res))
		// 	lstback_lex(res, lstnew_lex(ft_substr(result, 0, k), DQUOTE, 0));
		// else
		// 	lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(result, 0, k), 2);
		if (k < (int) ft_strlen(result))
			lexer(res, result + k + 1);
	}
	return (counter);
}

int	handle_squotes(t_lexargs **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	int		k;

	if (!ft_isspace(line, count, i))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	counter = i + 1;
	while (line[counter] != 39 && line[counter])
		counter++;
	if (line[counter] == 39)
		lstback_lex(res, lstnew_lex(ft_substr(line, i + 1, counter - i - 1), SQUOTE, 3));
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
			result = strjoin_helper(result, read, 1);
		}
		k = 0;
		while (result[k] && result[k] != 39)
			k++;
		lstback_lex(res, lstnew_lex(ft_substr(result, 0, k), SQUOTE, 0));
		if (k < (int) ft_strlen(result) - 1)
			lexer(res, result + k + 1);
	}
	return (counter);
}

int	handle_xor(t_lexargs **res, char *line, int i, int count)
{
	if (!(*res))
		return (parse_error("||"));
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else if (!ft_isspace(line, count, i))
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	lstback_lex(res, lstnew_lex("||", XOR, 2));
	return (i + 2);
}

int	handle_xand(t_lexargs **res, char *line, int i, int count)
{
	if (!(*res))
		return (parse_error("&&"));
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else if (!ft_isspace(line, count, i))
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	lstback_lex(res, lstnew_lex("&&", XAND, 2));
	return (i + 2);
}

int	handle_pipe(t_lexargs **res, char *line, int i, int count)
{
	if (!(*res))
		return (parse_error("|"));
	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else if (!ft_isspace(line, count, i))
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	lstback_lex(res, lstnew_lex("|", PIPE, 3));
	return (i + 1);
}

int	handle_heredoc(t_lexargs **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else if (!ft_isspace(line, count, i))
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	lstback_lex(res, lstnew_lex("<<", HEREDOC, 4));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 2);
	}
	return (parse_error("\\n"));
}

int	handle_wappend(t_lexargs **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else if (!ft_isspace(line, count, i))
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	lstback_lex(res, lstnew_lex(">>", WRITE_APPEND, 4));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 2);
	}
	return (parse_error("\n"));
}

int	handle_wtrunc(t_lexargs **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else if (!ft_isspace(line, count, i))
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	lstback_lex(res, lstnew_lex(">", WRITE_TRUNC, 4));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 1);
	}
	return (parse_error("\n"));
}

int	handle_input(t_lexargs **res, char *line, int i, int count)
{
	int	k;

	if (!ft_isspace(line, count, i) && is_delitimer(*res))
		lstback_lex(res, lstnew_lex(ft_substr(line, count, i - count), WORD, 0));
	else if (!ft_isspace(line, count, i))
		lstlast_lex(*res)->cmd = strjoin_helper(lstlast_lex(*res)->cmd, ft_substr(line, count, i - count), 0);
	lstback_lex(res, lstnew_lex("<", INPUT, 4));
	k = 1;
	while (line[i + ++k])
	{
		if (line[i + k] != ' ')
			return (i + 1);
	}
	return (parse_error("\n"));
}