/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:56:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/05 22:42:27 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mshell_exit(char **matrix, t_env *env, char *s);
int		exit_error_code(t_env *env);
int		check_exit_status(char **matrix, char *s, int exit_num);
char	*check_zeroes(char *str);

void	mshell_exit(char **matrix, t_env *env, char *s)
{
	long long	exit_num;
	char		*str;

	if (matrix[1] != NULL)
	{
		str = matrix[1];
		matrix[1] = check_zeroes(matrix[1]);
		free(str);
	}
	exit_num = ft_atll(matrix[1]);
	s = ft_itul(exit_num);
	if (matrix[1] && matrix[1][0] == '+' && matrix[1][0] == '-')
	{
		str = ft_strdup(s);
		if (matrix[1][0] == '+')
			s = ft_strjoin("+", str, -1);
		else if (matrix[1][0] == '-')
			s = ft_strjoin("-", str, -1);
		free(str);
	}
	if (matrixlen(matrix) == 1 && matrix[1] == NULL)
		exit(exit_error_code(env) + _free3_(s, matrix, NULL));
	exit_num = check_exit_status(matrix, s, exit_num);
	if (exit_num != 1000)
		exit(exit_num + _free3_(s, matrix, NULL));
}

int	exit_error_code(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "$?"))
			break ;
		tmp = tmp->next;
	}
	ft_dprintf(2, "exit\n");
	return (ft_atoi(tmp->data));
}

int	check_exit_status(char **matrix, char *s, int exit_num)
{
	if (matrixlen(matrix) == 2 && ft_strcmp(s, matrix[1]) == 0)
	{
		ft_dprintf(2, "exit\n");
		if (exit_num == 0)
			return (0);
		return (exit_num % 256);
	}
	else if (ft_strlen(s) > 19 || check_digit(matrix[1]) == 1 || \
		ft_strcmp(s, matrix[1]) != 0)
	{
		ft_dprintf(2, "exit\nMinishell: exit: %s: numeric argument required\n", \
			matrix[1]);
		return (255);
	}
	else if (matrixlen(matrix) > 2 && check_digit(matrix[1]) == 0)
	{
		ft_dprintf(2, "exit\nMinishell: exit: too many arguments\n");
		free(s);
		return (1000);
	}
	return (-1);
}

char	*check_zeroes(char *str)
{
	char	*tmp;

	if (str != NULL && (str[0] == '0' || \
			((str[0] == '+' || str[0] == '-') && str[1] == '0')))
	{
		tmp = ft_strdup(str);
		str = trim_zeroes(tmp);
		free(tmp);
	}
	return (ft_strdup(str));
}
