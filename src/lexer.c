/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/21 18:13:38 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex(char *line, t_list *env, t_init *init);
int		lexer(t_lexargs **res, char *line);

int	lexer(t_lexargs **res, char *line)
{
	int	i;
	int	l;
	int	counter;

	i = -1;
	l = -1;
	while (line[++i])
	{
		counter = i;
		while (line[i])
		{
			if (line[i] == '"')
				l = handle_dquotes(res, line, i, counter) + 1;
			else if (line[i] == 39)
				l = handle_squotes(res, line, i, counter) + 1;
			else if (line[i] == ')')
				l = parse_error(")");
			else if (line[i] == '(')
				l = handle_prnthses(res, line, i, counter);
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
	}
	return (1);
}

void	lex(char *line, t_list *env, t_init *init)
{
	//t_cmd	*cmd;
	int i = 0;
	//pid_t	pid;

	(void) env;
	init->lex = NULL;
	//cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(lexer(&init->lex, line)))
	{
		destroy_init(init);
		return ;
	}
	//find_path(cmd, env);
	//cmd->cmd_line = line;//cmd_processing(lex);
	//if (!check_cmd(cmd))
	//{
	//	pid = fork();
	//	if (pid == -1)
	//		printf ("Proccessing fault.\n");
	//	else if (pid == 0)
	//		execve(cmd->cmd_path, cmd->cmd_args, cmd->path);
	//	else
	//	{
	//		wait(NULL);
	//		free_matrix((void **) cmd->cmd_args);
	//		free(cmd->cmd_path);
	//		free(cmd);
	//		cmd = 0;
	//	}
	//}
	//int	i;
	//i = 0;
	while (init->lex)
	{
		printf("\033[38;5;54m[%d] --\ttype: %s\033[0m\n\tcmd: %s\n\tprecedence: %d\n", \
		i, get_token_name(init->lex->type), init->lex->cmd, init->lex->precedence);
		init->lex = init->lex->next;
		i++;
	}
	if (!is_valid(init))
	{
		destroy_init(init);
		return ;
	}
	parser(env, init);
}

/*
<< [whenever it's encountered -> it's heredoc]. It will be outputted only if there are cat are something like that
<< a | cat [wouldn't output something in any case, because heredoc in first part doesn't cat'ed]
			[in case of echo there are also nothing]
			[if there are nothing after << then whole line wouldn't executed and error will be outputed]
> [will insert the new info instead of old]
>> [will add the new info to the old]
*/