/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/15 15:51:41 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*some random functions that we need for mandatory one
//
//
//
//
//*/
typedef struct s_lexer_arg
{
	char	*cmd;
	void	*next;
}			t_lexargs;

void static	lexer(t_lexargs **res, char *line);

t_lexargs static	*ft_lstnew_3(char *content)
{
	t_lexargs	*elt;

	elt = (t_lexargs *)malloc(sizeof(t_lexargs));
	if (!elt)
		return (NULL);
	elt->cmd = content;
	elt->next = NULL;
	return (elt);
}

t_lexargs static	*ft_lstlast_2(t_lexargs *lst)
{
	t_lexargs *ptr;

	ptr = lst;
	if (!ptr)
		return (0);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void static	ft_lstadd_back_2(t_lexargs **lst, t_lexargs *new)
{
	t_lexargs	*ptr;

	ptr = ft_lstlast_2(*lst);
	if (!ptr)
		*lst = new;
	else
		ptr->next = new;
}
/*there is them all
//
//
//
//
*/

int static	ft_isspace(char *line, int i, int j)
{
	while(j < i && line[j])
	{
		if (line[j] != ' ' && line[j] != '	')
			return (0);
		j++;
	}
	return (1);
}

void static	handle_space(t_lexargs **res, char *line, int i, int count)
{
	if (ft_isspace(line, i, count))
		return ;
	ft_lstadd_back_2(res, ft_lstnew_3(ft_substr(line, count, i - count)));
}

int static	handle_dquotes(t_lexargs **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	char	*temp;
	int		k;

	if (!ft_isspace(line, i, count))
		ft_lstadd_back_2(res, ft_lstnew_3(ft_substr(line, count, i - count)));
	counter = i + 1;
	ft_lstadd_back_2(res, ft_lstnew_3("\""));
	while (line[counter] != '"' && line[counter])
		counter++;
	if (line[counter] == '"')
		ft_lstadd_back_2(res, ft_lstnew_3(ft_substr(line, i + 1, counter - i - 1)));
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i - 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("dquote> ");
			if (ft_strchr(read, '"'))
				enable = 0;
			temp = result;
			result = ft_strjoin(temp, "\n");
			free(temp);
			temp = result;
			result = ft_strjoin(temp, read);
			free(read);
			free(temp);
		}
		k = 0;
		while (result[k] && result[k] != '"')
			k++;
		ft_lstadd_back_2(res, ft_lstnew_3(ft_substr(result, 0, k)));
		if (k < (int) ft_strlen(result))
			lexer(res, result + k + 1);
	}
	ft_lstadd_back_2(res, ft_lstnew_3("\""));
	return (counter);
}

int static	handle_squotes(t_lexargs **res, char *line, int i, int count)
{
	int		counter;
	int		enable;
	char	*read;
	char	*result;
	char	*temp;
	int		k;

	if (!ft_isspace(line, i, count))
		ft_lstadd_back_2(res, ft_lstnew_3(ft_substr(line, count, i - count)));
	counter = i + 1;
	ft_lstadd_back_2(res, ft_lstnew_3("'"));
	while (line[counter] != 39 && line[counter])
		counter++;
	if (line[counter] == 39)
		ft_lstadd_back_2(res, ft_lstnew_3(ft_substr(line, i + 1, counter - i - 1)));
	else
	{
		enable = 1;
		result = ft_substr(line, i + 1, counter - i - 1);
		if (!result)
			ft_strdup(result);
		while (enable)
		{
			read = readline("quote> ");
			if (ft_strchr(read, 39))
				enable = 0;
			temp = result;
			result = ft_strjoin(temp, "\n");  
			free(temp);
			temp = result;
			result = ft_strjoin(temp, read);
			free(read);
			free(temp);
		}
		k = 0;
		while (result[k] && result[k] != 39)
			k++;
		ft_lstadd_back_2(res, ft_lstnew_3(ft_substr(result, 0, k)));
		if (k < (int) ft_strlen(result) - 1)
			lexer(res, result + k + 1);
	}
	ft_lstadd_back_2(res, ft_lstnew_3("'"));
	return (counter);
}

void static	lexer(t_lexargs **res, char *line)
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

void	lex(char *line)
{
	t_lexargs	*res;

	res = NULL;
	lexer(&res, line);
	while (res)
	{
		printf("lexing resulte: %s\n", res->cmd);
		res = res->next;
	}
}