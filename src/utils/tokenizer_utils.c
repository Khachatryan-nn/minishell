/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:41:52 by tikhacha          #+#    #+#             */
/*   Updated: 2023/10/20 00:17:46 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_heredoc_input(t_init *init, t_tok *tok, char *str, t_env *env);
int		add_new_quote(t_tok **res, char *line, int i, int type);
int		read_heredoc(char *line, char **result, char *limiter);
void	expand_heredoc(char *result, int fd, t_env *env);
void	find_limiter(t_init *init, t_tok *stack);

int	handle_heredoc_input(t_init *init, t_tok *tok, char *str, t_env *env)
{
	char	*result;

	result = NULL;
	tok->hdoc_fname = ft_strdup(init->hd->fn[++init->hd->i]);
	tok->fd = open(tok->hdoc_fname, O_RDWR | O_CREAT | O_TRUNC, 00655);
	find_limiter(init, tok->next);
	call_signals(4);
	while (1)
	{
		if (g_exit_status_ == 130)
		{
			free(result);
			init->exit_status = 1;
			return (130);
		}
		if (!read_heredoc(str, &result, tok->next->cmd))
			break ;
	}
	expand_heredoc(result, tok->fd, env);
	return (1);
}

int	read_heredoc(char *str, char **result, char *limiter)
{
	str = readline("> ");
	if (!str || !ft_strcmp(str, limiter))
	{
		free (str);
		return (0);
	}
	if (!(*result))
		*result = ft_strdup(str);
	else
		*result = strjoin_helper(*result, str, 1);
	free (str);
	return (1);
}

void	expand_heredoc(char *result, int fd, t_env *env)
{
	t_exp	exp;
	char	*new;

	exp.i = -1;
	exp.l = 0;
	exp.str = NULL;
	exp.s = NULL;
	new = NULL;
	if (result)
		result = ft_strjoin(result, "\n", 1);
	else
		result = ft_strdup("");
	if (ft_strchr(result, '$'))
	{
		new = ft_strdup(expand(result, env, &exp));
		free(result);
		result = ft_strdup(new);
		free(new);
	}
	write(fd, result, ft_strlen(result));
	_close2_(fd, _free3_(result, NULL, NULL) - 42);
	destroy_exp(&exp);
}

int	add_new_quote(t_tok **res, char *line, int i, int type)
{
	int		counter;
	char	c;
	char	*str;

	c = '\0';
	if (type == DQUOTE)
		c = '"';
	else if (type == SQUOTE)
		c = '\'';
	counter = i + 1;
	while (line[counter] && line[counter] != c)
		counter++;
	if (line[i] == '\'' || line[i] == '"')
		str = ft_substr(line, i + 1, counter - i - 1);
	else
		str = ft_substr(line, i, counter - i);
	if (line[counter] == c && is_delimiter(*res))
		lstback(res, lstnew_pars(str, type, 0, 1));
	else if (line[counter] == c && i > 1 && line[i - 1] == ' ')
		lstback(res, lstnew_pars(str, type, 0, 2));
	else if (line[counter] == c)
		lstback(res, lstnew_pars(str, type, 0, 0));
	free(str);
	return (counter);
}

void	find_limiter(t_init *init, t_tok *stack)
{
	t_tok	*tmp;
	t_tok	*cmd_l;

	tmp = stack->next;
	cmd_l = stack->prev->prev;
	while (tmp && tmp->cmd && is_wrd(tmp) && !(tmp->flag & 1 << 1))
	{
		stack->cmd = ft_strjoin(stack->cmd, tmp->cmd, 1);
		tmp = tmp->next;
		pop_redir(tmp->prev);
	}
	while (cmd_l->prev && check_type(cmd_l->prev->type) == 2)
		cmd_l = cmd_l->prev->prev;
	if (cmd_l->cmd && !ft_strcmp(cmd_l->cmd, "(NULL)") \
		&& tmp->cmd && !is_wrd(tmp))
		return ;
	if (tmp && tmp->cmd && is_wrd(tmp))
		if_implementation(&tmp, &cmd_l);
	if (cmd_l->cmd && !ft_strcmp(cmd_l->cmd, "(NULL)") && !cmd_l->prev)
	{
		init->lex = init->lex->next;
		init->lex->flag |= 1;
		pop_redir(cmd_l);
	}
}
