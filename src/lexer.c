/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/18 02:15:22 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_lexargs **res, char *line);

void	lexer(t_lexargs **res, char *line)
{
	int			i;
	int			counter;

	i = -1;
	while (line[++i])
	{
		counter = i;
		while (line[i])
		{
			if (line[i] == '"')
			{
				i = handle_dquotes(res, line, i, counter) + 1;
				break ;
			}
			else if (line[i] == 39)
			{
			 	i = handle_squotes(res, line, i, counter) + 1;
				break ;
			}
			else if (line[i] == '(')
			{//if there are more than one parenthesis, then it's math>
				i = handle_op_parentheses(res, line, i, counter);
				break ;
			}
			else if (line[i] == ' ')
			{
				handle_space(res, line, i, counter);
				break ;
			}
			// else if (line[i] == "|" && line[i + 1] == "|")
			// 	handle_xor(line, i, counter);
			// else if (line[i] == "&" && line[i + 1] == "&")
			// 	handle_xand(line, i, counter);
			// else if (line[i] == '|')
			// 	handle_pipe(line, i, counter);
			// else if (line[i] == '&')
			// 	handle_single_and(line, i, counter);
			// else if (line[i] == '<' && line[i + 1] == '<')
			// 	handle_heredoc(line, i, counter);
			else if (line[i + 1] == '\0')
			{
				handle_space(res, line, i + 1, counter);
				break ;
			}
			i++;
		}
	}
}

void	lex(char *line, t_list *env)
{
	t_lexargs	*res;
	int			done;
	(void)		done;
	(void)		env;

	res = NULL;
	lexer(&res, line);
	//while (res)
	//{
	// 	// printf("lexing resulte: %s\n", res->cmd);
	// 	done = -1;
	// 	while (env && done == -1)
	// 	{
	// 		env = env->next;
	//		done = access(res->cmd, X_OK);
	// 		if (done)
	//			execve(0, res->cmd, env->content);
	// 	}
	// 	if (done == -1)
	// 		perror("Execve err");
	// 	res = res->next;
	// 	free(res->cmd);
	//}
	free(res);
}