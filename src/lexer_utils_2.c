/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:19:28 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/21 18:57:12 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	strjoin_helper(char *read, char *result);

void	strjoin_helper(char *read, char *result)
{
	char	*temp;

	temp = result;
	result = ft_strjoin(temp, "\n");
	free(temp);
	temp = result;
	result = ft_strjoin(temp, read);
	free(read);
	free(temp);
}
