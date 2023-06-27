/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/27 18:58:01 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex(char *line, t_list *env, char **env1);
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
				i = handle_prnthses(res, line, i, counter);
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

void	lex(char *line, t_list *env, char **env1)
{
	t_lexargs	*res;
	t_cmd		*cmd;
	pid_t		pid;
	int			done;

	(void) done;
	(void) env1;
	res = NULL;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	lexer(&res, line);
	find_path(cmd, env);
	cmd->cmd_line = line;
	if (!check_cmd(cmd))
	{
		pid = fork();
		if (pid == -1)
			printf ("Proccessing fault.\n");
		else if (pid == 0)
			execve(cmd->cmd_path, cmd->cmd_args, cmd->path);
		else
		{
			wait(NULL);
			free(cmd->cmd_line);
			free_matrix((void **) cmd->cmd_args);
			free(cmd->cmd_path);
			free(cmd);
			cmd = 0;
		}
	}
	int	i;
	i = 0;
	while (res)
	{
		printf("\033[38;5;54m[%d] --\ttype: %s\033[0m\n\tcmd: %s\n", \
		i, get_token_name(res->type), res->cmd);
		res = res->next;
		i++;
	}
	ft_lstclear_3(&res);
}
