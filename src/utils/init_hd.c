/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:59:57 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/02 13:02:31 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_hd(t_hd **hd);

void	init_hd(t_hd **hd)
{
	int		i;
	char	*str;

	i = 0;
	if (*hd)
		return ;
	(*hd) = (t_hd *)malloc(sizeof(t_hd));
	(*hd)->i = -1;
	(*hd)->matrix = (char **)malloc(sizeof(char *) * 16);
	while (i < 16)
	{
		(*hd)->matrix[i] = ft_strdup(".heredoc");
		str = ft_itoa(i);
		(*hd)->matrix[i] = ft_strjoin((*hd)->matrix[i], str, 1);
		free(str);
		i++;
	}
}
