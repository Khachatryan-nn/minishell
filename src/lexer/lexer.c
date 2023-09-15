/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/15 21:30:33 by tikhacha         ###   ########.fr       */
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

char	*inner_while(t_tok **res, char **line, int *i, int counter)
{
	char	*key;

	while ((*line)[*i])
	{
		if ((*line)[*i] == '"' || (*line)[*i] == '\'')
		{
			key = handle_quotes(res, line, i, counter);
			if (key)
				return (key);
		}
		else if (!handle_tokens_p1(res, line, i, counter))
		{
			(*i)++;
			continue ;
		}
		break ;
	}
	return (NULL);
}

int	lexer(t_tok **res, char **line)
{
	int		i;
	int		counter;

	i = 0;
	while (*line && (*line)[i])
	{
		counter = i;
		inner_while(res, line, &i, counter);
		i++;
	}
	lstback(res, lstnew_pars("AST", END, 1, 2));
	return (1);
}

void	lex(char **line, t_init *init, t_env *env)
{
	t_tok	*tmp;
	int		sb;

	sb = 0;
	tmp = init->lex;
	heredoc_validation(init, tmp);
	if (!lexer(&init->lex, line) || !init->lex || !is_valid(init, env, sb))
	{
		unlink_heredocs(init);
		destroy_init(init);
		init->exit_status = 258;
		return ;
	}
	parser(init, env);
}

//ls && pwdw || (ls | cat -e | cat -e | cat -e) > file1