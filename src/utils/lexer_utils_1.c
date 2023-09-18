/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:07:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/18 18:41:32 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_validation(t_init *init, t_tok *tok);
int		ft_isspace(char *line, int i, int j);
int		quote_count(char *line, char c);
t_type	token_name(char *token);

//Checks if there only spaces from i -> j.\
//If there are only spaces returns 1.
int	ft_isspace(char *line, int i, int j)
{
	while (i < j && line[i])
	{
		if (line[i] != ' ' && line[i] != '	')
			return (0);
		i++;
	}
	return (1);
}

t_type	token_name(char *token)
{
	if (token[0] == '"')
		return (DQUOTE);
	else if (token[0] == '\'')
		return (SQUOTE);
	else if (token[0] == '(')
		return (SUBSH_OPEN);
	else if (token[0] == ')')
		return (SUBSH_CLOSE);
	else if (token[0] == '|' && token[1] == '|')
		return (XOR);
	else if (token[0] == '&' && token[1] == '&')
		return (XAND);
	else if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '<' && token[1] == '<')
		return (HEREDOC);
	else if (token[0] == '>' && token[1] == '>')
		return (WR_APPEND);
	else if (token[0] == '>')
		return (WR_TRUNC);
	else if (token[0] == '<')
		return (INPUT);
	else if (token[0] == '\0')
		return (END);
	return (WORD);
}

void	unlink_heredocs(t_init	*init)
{
	t_tok	*tok;

	tok = init->lex;
	while (tok)
	{
		if (tok->type == HEREDOC && tok->hdoc_fname)
			unlink(tok->hdoc_fname);
		tok = tok->next;
	}
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
		ft_dprintf(2, "minishell: maximum here-document count exceeded\n");
		destroy_init(init);
		exit(2);
	}
}

int	quote_count(char *line, char c)
{
	int	dquote;
	int	squote;
	int	i;

	i = -1;
	dquote = ((squote = 0));
	while (line && line[++i])
	{
		if (line[i] == '"')
			dquote++;
		if (line[i] == '\'')
			squote++;
	}
	if (c == '\'')
		return (squote);
	else if (c == '"')
		return (dquote);
	return (dquote + squote);
}
