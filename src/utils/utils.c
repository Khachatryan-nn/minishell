/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:17 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/13 22:18:13 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_helper(char *result, char *read, int mode);
int		ft_strcmp( char *s1, char *s2);
int		ft_onlyspaces(char *str);
int		matrixlen(char **matrix);
int		check_digit(char *str);

/// @brief
/// @param mode 1 -> new line
///	@param mode else -> space
char	*strjoin_helper(char *result, char *read, int mode)
{
	if (mode == 1)
		result = ft_strjoin(result, "\n", 1);
	else
		result = ft_strjoin(result, " ", 1);
	result = ft_strjoin(result, read, 1);
	return (result);
}

int	ft_onlyspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/// @brief
/// @return 0 if there are equal
///	@return or difference between non-eq. symbols
int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	matrixlen(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix && matrix[i] != NULL)
		i++;
	return (i);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str && str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}
