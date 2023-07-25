/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:07:29 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 11:37:26 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_isspace(char *line, int i, int j);

//Checks if there only spaces from i -> j.\
//If there are only spaces returns 1.
int	ft_isspace(char *line, int i, int j)
{
	while (i < j && line[i])
	{
		if (line[i] != ' ' && line[i] != '	')
			return (0);
		i++;
	}
	return (1);
}