/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/08 16:46:30 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex(char *line,  t_init *init);
int		lexer(t_parser **res, char *line);

int	lexer(t_parser **res, char *line)
{
	int	i;
	int	l;
	int	counter;
	int	subsh;

	i = 0;
	l = -1;
	subsh = 0;
	while (line && line[i] != '\0')
	{
		counter = i;
		while (line[i] != '\0')
		{
			if (line[i] == '"')
				l = handle_dquotes(res, line, i, counter) + 1;
			else if (line[i] == 39)
				l = handle_squotes(res, line, i, counter) + 1;
			else if (line[i] == ')')
			{
				if (subsh)
				{
					l = handle_cprnthses(res, line, i, counter);
					subsh--;
				}
				else
					l = parse_error(")", 0);
			}
			else if (line[i] == '(')
			{
				if (handle_prnthses(res, line, i, counter))
				{
					subsh++;
					l = -1;
				}
				else
					l = 0;
			}
			else if (line[i] == '|' && line[i + 1] == '|')
				l = handle_xor(res, line, i, counter);
			else if (line[i] == '&' && line[i + 1] == '&')
				l = handle_xand(res, line, i, counter);
			else if (line[i] == '<' && line[i + 1] == '<')
				l = handle_heredoc(res, line, i, counter);
			else if (line[i] == '>' && line[i + 1] == '>')
				l = handle_wappend(res, line, i, counter);
			else if (line[i] == '>')
				l = handle_wtrunc(res, line, i, counter);
			else if (line[i] == '<')
				l = handle_input(res, line, i, counter);
			else if (ft_strchr(" \n\t\v\r\f", line[i]))
				handle_space(res, line, i, counter);
			else if (line[i] == '|')
				l = handle_pipe(res, line, i, counter);
			else if (line[i + 1] == '\0')
				handle_space(res, line, i + 1, counter);
			else
			{
				i++;
				continue ;
			}
			if (l == 0)
				return (0);
			else if (l > 0)
			{
				i = l;
				l = -1;
			}
			break ;
		}
		if (line[i] == '\0')
			break ;
		i++;
	}
	lstback(res, lstnew_pars("AST", END, 1, 2));
	return (1);
}

void	lex(char *line, t_init *init)
{
	init->lex = NULL;
	if (!(lexer(&init->lex, line)))
	{
		destroy_init(init);
		init->exit_status = 258;
		return ;
	}
	if (!is_valid(init))
	{
		destroy_init(init);
		init->exit_status = 258;
		return ;
	}
	parser(init);
}