/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:41:52 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/08 17:43:19 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_input(char	*limiter, t_parser **res);

void	heredoc_input(char	*limiter, t_parser **res)
{
	char	*line;
	char	*result;

	line = NULL;
	result = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		if (!result)
			result = line;
		else
			result = strjoin_helper(result, line, 1);
	}
	lstback(res, lstnew_pars(result, WORD, 0, 1));
}
