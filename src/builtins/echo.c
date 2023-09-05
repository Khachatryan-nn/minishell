/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:52:40 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 23:54:08 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mshell_echo(char **matrix);

void	mshell_echo(char **matrix)
{
	int	j;
	int	i;

	i = 1;
	j = 1;
	if (matrix[1] == NULL)
		printf("\n");
	if (matrix[i] && ft_strncmp(matrix[i], "-n", 2) == 0)
	{
		while (matrix[i] != NULL && ft_strncmp(matrix[i], "-n", 2) == 0)
		{
			j = 1;
			while (matrix[i][j] && matrix[i][j] == 'n')
				j++;
			if (matrix[i][j] != '\0')
				break ;
			else if (matrix[i + 1] && ft_strncmp(matrix[i + 1], "-n", 2) != 0)
			{
				while (matrix[i + 1])
				{
					printf("%s", matrix[i + 1]);
					if (matrix[i + 2])
						printf(" ");
					i++;
					if (matrix[i + 1] == NULL)
						return ;
				}
			}
			i++;
		}
		while (matrix[i] && i != 1)
		{
			printf("%s", matrix[i]);
			if (matrix[i + 1])
				printf(" ");
			i++;
			if (matrix[i] == NULL)
				return ;
		}
	}
	if (matrix[i] && (ft_strncmp(matrix[i], "-n", 2) != 0 || i == 1))
	{
		while (matrix[i])
		{
			printf("%s", matrix[i]);
			if (matrix[i + 1])
				printf(" ");
			i++;
			if (matrix[i] == NULL)
				printf("\n");
		}
	}	
}
