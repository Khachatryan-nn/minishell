/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:46:00 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 23:46:17 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long int	ft_atll(char *str);
char	*trim_zeroes(char *s);

char	*trim_zeroes(char *s)
{
	int		j;
	char	*str;

	j = 0;
	str = NULL;
	if (s[j] == '-' || s[j] == '+')
		j++;
	if (s[j] == '0' || (s[j] == '0' && s[j + 1] == '0'))
	{
		while (s && s[j] != '\0')
		{
			while (s[j] != '\0' && s[j] == '0')
				j++;
			if (s[j] != '0')
				break ;
		}
		if (s[j] != '\0' && s[j] != '0')
			str = (char *)malloc(sizeof(char) * (j + 1));
		if (!str)
			return (ft_strdup("0"));
		str = ft_strdup(&s[j]);
		return (str);
	}
	return (s);
}

unsigned long long int	ft_atll(char *str)
{
	long long	num;
	int			sing;

	sing = 1;
	num = 0;
	if (!str)
		return (0);
	while (*str && ((*str == ' ') || *str == '\t' || *str == '\r'
			|| *str == '\f' || *str == '\v' || *str == '\n'))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sing *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		++str;
	}
	return (num * sing);
}
