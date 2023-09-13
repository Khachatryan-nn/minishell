/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:46:00 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/13 22:05:48 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long int	ft_atll(char *str);
char					*trim_zeroes(char *s);

char	*trim_zeroes(char *s)
{
	int		j;

	j = 0;
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
		if (s[j] == '\0')
			return (ft_strdup("0"));
		return (ft_strdup(&s[j]));
	}
	return (ft_strdup(s));
}

unsigned long long int	ft_atll(char *str)
{
	long long	num;
	int			sign;
	int			i;

	sign = 1;
	num = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && ((str[i] == ' ') || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n'))
		i++;
	if (str && str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}
