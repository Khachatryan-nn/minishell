/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/10/16 19:54:08 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_tokens_p1(t_tok **res, char **line, int *i, int counter);
void	lex(char **line, t_init *init, t_env *env);
int		lexer(t_tok **res, char **line);

int	handle_tokens_p1(t_tok **res, char **line, int *i, int counter)
{
	if ((*line)[*i] == ')')
		*i = handle_cprnthses(res, *line, *i, counter);
	else if ((*line)[*i] == '(')
		*i = handle_prnthses(res, *line, *i, counter);
	else if ((*line)[*i] == '|' && (*line)[*i + 1] == '|')
		*i = handle_xor(res, *line, *i, counter);
	else if ((*line)[*i] == '&' && (*line)[*i + 1] == '&')
		*i = handle_xand(res, *line, *i, counter);
	else if ((*line)[*i] == '<' && (*line)[*i + 1] == '<')
		*i = handle_heredoc(res, *line, *i, counter);
	else if ((*line)[*i] == '>' && (*line)[*i + 1] == '>')
		*i = handle_wappend(res, *line, *i, counter);
	else if ((*line)[*i] == '>')
		*i = handle_wtrunc(res, *line, *i, counter);
	else if ((*line)[*i] == '<')
		*i = handle_input(res, *line, *i, counter);
	else if ((*line)[*i] == '|')
		*i = handle_pipe(res, *line, *i, counter);
	else if (ft_strchr(" \n\t\v\r\f\0", (*line)[*i]))
		handle_space(res, *line, *i, counter);
	else if ((*line)[*i + 1] == '\0')
		handle_space(res, *line, *i + 1, counter);
	else
		return (0);
	return (1);
}

int	inner_while(t_tok **res, char **line, int *i, int counter)
{
	while ((*line)[*i])
	{
		if ((*line)[*i] == '"' || (*line)[*i] == '\'')
			handle_quotes(res, line, i, counter);
		else if (!handle_tokens_p1(res, line, i, counter))
		{
			(*i)++;
			continue ;
		}
		if (*i < 0)
			return (1);
		break ;
	}
	return (0);
}

int	lexer(t_tok **res, char **line)
{
	int		i;
	int		counter;

	i = 0;
	while (*line && (*line)[i])
	{
		counter = i;
		if (inner_while(res, line, &i, counter))
			return (0);
		i++;
	}
	lstback(res, lstnew_pars("AST", END, 1, 2));
	return (1);
}

void	lex(char **line, t_init *init, t_env *env)
{
	int		sb;

	sb = 0;
	g_exit_status_ = 0;
	if (!lexer(&init->lex, line) || !init->lex)
	{
		destroy_init(init);
		init->exit_status = 258;
		return ;
	}
	heredoc_validation(init, NULL);
	if (!is_valid(init, env, &sb, 1) || sb > 0 \
		|| !is_valid(init, env, &sb, 0))
	{
		if (sb > 0)
			ft_dprintf(2, "minishell: syntax error: missing token `)'\n");
		unlink_heredocs(init);
		destroy_init(init);
		init->exit_status = 258;
		return ;
	}
	check_redir(&init->lex);
	parser(init, env);
}
