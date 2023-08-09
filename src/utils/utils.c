/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:17 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/08 16:57:24 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_helper(char *result, char *read, int mode);
int		ft_strcmp( char *s1, char *s2);
int		ft_onlyspaces(char *str);

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
int	ft_strcmp( char *s1, char *s2)
{
	int		i;
	char	*ptr1;
	char	*ptr2;

	i = 0;
	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	if (!s1 && !s2)
		return (0);
	while (ptr1[i] && ptr2[i] && ptr1[i] == ptr2[i])
	{
		if (ptr1[i] == '\0' && ptr2[i] == '\0')
			return (0);
		i++;
	}
	return (ptr1[i] - ptr2[i]);
}
