/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/02 23:01:21 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex(char *line, t_list *env);
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
				i = handle_dquotes(res, line, i, counter) + 1;
			else if (line[i] == 39)
				i = handle_squotes(res, line, i, counter) + 1;
			else if (line[i] == '(')
				i = handle_prnthses(res, line, i, counter);
			else if (line[i] == '|' && line[i + 1] == '|')
				i = handle_xor(res, line, i, counter);
			else if (line[i] == '&' && line[i + 1] == '&')
				i = handle_xand(res, line, i, counter);
			else if (line[i] == '<' && line[i + 1] == '<')
				i = handle_heredoc(res, line, i, counter);
			else if (line[i] == '>' && line[i + 1] == '>')
				i = handle_wappend(res, line, i, counter);
			else if (line[i] == '>')
				i = handle_wtrunc(res, line, i, counter);
			else if (line[i] == ' ')
				handle_space(res, line, i, counter);
			else if (line[i] == '|')
				handle_pipe(res, line, i, counter);
			else if (line[i] == '&')
				handle_and(res, line, i, counter);
			else if (line[i + 1] == '\0')
				handle_space(res, line, i + 1, counter);
			else
			{
				i++;
				continue ;
			}
			break ;
		}
	}
}

void	lex(char *line, t_list *env)
{
	t_lexargs	*res;
	t_cmd		*cmd;
	pid_t		pid;

	res = NULL;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	lexer(&res, line);
	find_path(cmd, env);
	cmd->cmd_line = line;//cmd_processing(res);
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

/*

<< [whenever it's encountered -> it's heredoc]. It will be outputted only if there are cat are something like that
<< a | cat [wouldn't output something in any case, because heredoc in first part doesn't cat'ed]
			[in case of echo there are also nothing]
			[if there are nothing after << then whole line wouldn't executed and error will be outputed]
> [will insert the new info instead of old]
>> [will add the new info to the old]
*/