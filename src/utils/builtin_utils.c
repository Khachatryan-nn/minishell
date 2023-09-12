/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:46:00 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/12 16:16:26 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long int	ft_atll(char *str);
char					*trim_zeroes(char *s);

char	*trim_zeroes(char *s)
{
	char	*tmp;

	if (s != NULL && ((s[0] == '0' && s[1] == '0') || \
			((s[0] == '+' || s[0] == '-') && s[1] == '0')))
	{
		tmp = ft_strdup(s);
		free(s);
		s = trim_zeroes(tmp);
		if (ft_strchr(tmp, '+') || ft_strchr(tmp, '-'))
			s = num_sign(s, tmp[0]);
		free(tmp);
		return (s);
	}
	else
		return (s);
}

unsigned long long int	ft_atll(char *str)
{
	long long	num;
	int			sing;
	int			i;

	sing = 1;
	num = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && ((str[i] == ' ') || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sing *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sing);
}
