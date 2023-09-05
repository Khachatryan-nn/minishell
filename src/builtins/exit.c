/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:56:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/05 16:48:14 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_exit_status(char **arr, char *s, int exit_num);
void	mshell_exit(char **arr, t_env *env, char *s);
int		exit_error_code(t_env *env);

void	mshell_exit(char **arr, t_env *env, char *s)
{
	long long	exit_num;
	char		*str;

	if (arr[1] != NULL && (arr[1][0] == '0' || arr[1][0] == '+'))
	{
		str = arr[1];
		arr[1] = trim_zeroes(arr[1]);
		free(str);
	}
	exit_num = ft_atll(arr[1]);
	s = ft_itul(exit_num);
	if (arr[1] && arr[1][0] == '+')
	{
		str = s;
		s = ft_strjoin("+", s, -1);
		free(str);
	}
	if (matrixlen(arr) == 1 && arr[1] == NULL)
		exit(exit_error_code(env));
	exit_num = check_exit_status(arr, s, exit_num);
	if (exit_num != -1)
		exit(exit_num + _free3_(s, arr, NULL));
	free(s);
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
	printf("exit\n");
	return(ft_atoi(tmp->data));
}

int	check_exit_status(char **arr, char *s, int exit_num)
{
	if (matrixlen(arr) == 2 && ft_strcmp(s, arr[1]) == 0)
	{
		ft_dprintf(2, "exit\n");
		if (exit_num == 0)
			return (0);
		return (exit_num % 256);
	}
	else if (ft_strlen(s) > 19 || check_digit(arr[1]) == 1 || \
		ft_strcmp(s, arr[1]) != 0)
	{
		ft_dprintf(2, "exit\n Minishell: exit: %s: numeric argument required\n", \
			arr[1]);
		return (255);
	}
	else if (matrixlen(arr) > 2 && check_digit(arr[1]) == 0)
	{
		ft_dprintf(2, "exit\n Minishell: exit: too many arguments\n");
		return (-1);
	}
	return (-1);
}
