/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:38:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/12 18:53:23 by tikhacha         ###   ########.fr       */
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

void static	handle_space(t_lexargs **res, char *line, int i, int j)
{
	//int	counter;

	ft_lstadd_back_2(res, ft_lstnew_3(ft_substr(line, j, i)));
}

void	lexer(char *line)
{
	int			i;
	int			counter;
	t_lexargs	*res;

	i = -1;
	res = NULL;
	while (line[++i])
	{
		counter = i;
		while (line[i])
		{
			if (line[i] == ' ')
			{
				handle_space(&res, line, i, counter);
				printf("%d %d\n", counter, i);
				break ;
			}
			//else if (line[i] == '"')
			//	handle_double_quotes(line, i, counter);
			// else if (line[i] == 39)
			// 	handle_single_quotes(line, i, counter);
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
			i++;
		}
	}
	while (res)
	{
		printf("there we are: %s\n", res->cmd);
		res = res->next;
	}
}