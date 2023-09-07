/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:52:40 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 23:19:22 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int static	echo_part1(char **arr, int i);
void static	echo_part2(int i, char **arr);
void		mshell_echo(char **arr);

void	mshell_echo(char **arr)
{
	int	i;

	i = 1;
	if (arr[1] == NULL)
		printf("\n");
	if (arr[i] && ft_strncmp(arr[i], "-n", 2) == 0)
	{
		i = echo_part1(arr, i);
		if (i == 0)
			return ;
		while (arr[i] && i != 1)
		{
			printf("%s", arr[i]);
			if (arr[i + 1])
				printf(" ");
			i++;
			if (arr[i] == NULL)
				return ;
		}
	}
	if (arr[i] && (ft_strncmp(arr[i], "-n", 2) != 0 || i == 1))
		echo_part2(i, arr);
}

int static	echo_part1(char **arr, int i)
{
	int	j;

	while (arr[i] != NULL && ft_strncmp(arr[i], "-n", 2) == 0)
	{
		j = 1;
		while (arr[i][j] && arr[i][j] == 'n')
			j++;
		if (arr[i][j] != '\0')
			break ;
		else if (arr[i + 1] && ft_strncmp(arr[i + 1], "-n", 2) != 0)
		{
			while (arr[i + 1])
			{
				printf("%s", arr[i + 1]);
				if (arr[i + 2])
					printf(" ");
				i++;
				if (arr[i + 1] == NULL)
					return (0);
			}
		}
		i++;
	}
	return (i);
}

void static	echo_part2(int i, char **arr)
{
	while (arr[i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(" ");
		i++;
		if (arr[i] == NULL)
			printf("\n");
	}
}
