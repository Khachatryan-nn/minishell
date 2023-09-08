/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/08 15:08:04 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer(t_tok **res, char **line);
void	lex(char **line, t_init *init);

int	lexer(t_tok **res, char **line)
{
	int	i;
	int	counter;
	int	subsh;

	i = 0;
	subsh = 0;
	while (*line && i < (int) ft_strlen(*line))
	{
		counter = i;
		while (i < (int) ft_strlen(*line))
		{
			if ((*line)[i] == '"')
				i = handle_dquotes(res, line, i, counter);
			else if ((*line)[i] == 39)
				i = handle_squotes(res, line, i, counter);
			else if ((*line)[i] == ')')
			{
				if (subsh)
				{
					i = handle_cprnthses(res, *line, i, counter);
					subsh--;
				}
				else
					i = parse_error(")", 0);
			}
			else if ((*line)[i] == '(' && \
				handle_prnthses(res, *line, i, counter))
					subsh++;
			else if ((*line)[i] == '|' && (*line)[i + 1] == '|')
				i = handle_xor(res, *line, i, counter);
			else if ((*line)[i] == '&' && (*line)[i + 1] == '&')
				i = handle_xand(res, *line, i, counter);
			else if ((*line)[i] == '<' && (*line)[i + 1] == '<')
				i = handle_heredoc(res, *line, i, counter);
			else if ((*line)[i] == '>' && (*line)[i + 1] == '>')
				i = handle_wappend(res, *line, i, counter);
			else if ((*line)[i] == '>')
				i = handle_wtrunc(res, *line, i, counter);
			else if ((*line)[i] == '<')
				i = handle_input(res, *line, i, counter);
			else if ((*line)[i] == '|')
				i = handle_pipe(res, *line, i, counter);
			else if (ft_strchr(" \n\t\v\r\f\0", (*line)[i]))
				handle_space(res, *line, i, counter);
			else if ((*line)[i + 1] == '\0')
				handle_space(res, *line, i + 1, counter);
			else
			{
				i++;
				continue;
			}
			i++;
			break;
		}
	}
	lstback(res, lstnew_pars("AST", END, 1, 2));
	return (1);
}

void	lex(char **line, t_init *init)
{
	t_tok	*tmp;

	if (!lexer(&init->lex, line) || !is_valid(init))
	{
		destroy_init(init);
		init->exit_status = 258;
		return ;
	}
	tmp = init->lex;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (tmp->next->next->type == WR_APPEND || tmp->next->next->type == WR_TRUNC)
				init->redir = 1;
			init->hdoc++;
		}
		tmp = tmp->next;
	}
	if (init->hdoc > 15)
	{
		ft_dprintf(2, "minishell: maximum here-document count exceeded");
		exit(2);
	}
	parser(init);
}
