/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/09 02:25:42 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer(t_tok **res, char **line);
void	lex(char **line, t_init *init, t_env *env);

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

int	lexer(t_tok **res, char **line)
{
	int	i;
	int	counter;

	i = 0;
	while (*line && (*line)[i])
	{
		counter = i;
		while ((*line)[i])
		{
			if ((*line)[i] == '"')
				i = handle_dquotes(res, line, i, counter);
			else if ((*line)[i] == 39)
				i = handle_squotes(res, line, i, counter);
			else if (!handle_tokens_p1(res, line, &i, counter))
			{
				i++;
				continue ;
			}
			i++;
			break ;
		}
	}
	lstback(res, lstnew_pars("AST", END, 1, 2));
	return (1);
}

void	heredoc_validation(t_init *init, t_tok *tok)
{
	tok = init->lex;
	while (tok)
	{
		if (tok->type == HEREDOC)
		{
			if (tok->next->next->type == WR_APPEND || \
				tok->next->next->type == WR_TRUNC)
				init->redir = 1;
			init->hdoc++;
		}
		tok = tok->next;
	}
	if (init->hdoc > 15)
	{
		ft_dprintf(2, "minishell: maximum here-document count exceeded");
		exit(2);
	}
}

void	lex(char **line, t_init *init, t_env *env)
{
	t_tok	*tmp;

	tmp = init->lex;
	heredoc_validation(init, tmp);
	if (!lexer(&init->lex, line) || !init->lex || !is_valid(init, env))
	{
		destroy_init(init);
		init->exit_status = 258;
		return ;
	}
	parser(init, env);
}
