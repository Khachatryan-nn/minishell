/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:41:52 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/30 20:43:18 by tikhacha         ###   ########.fr       */
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
		ft_dprintf(1, "> ");
		line = get_next_line(0);
		if (!ft_strcmp(line, limiter))
			break ;
		else
			result = ft_strjoin(result, line, 1);
	}
	//lstlast(*res)->val = result;
	lstback(res, lstnew_pars(result, WORD, 0, 1));
}
