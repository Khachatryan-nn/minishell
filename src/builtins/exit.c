/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:56:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 23:54:38 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mshell_exit(char **matrix, t_env *env);

void	mshell_exit(char **matrix, t_env *env)
{
	char		*s;
	t_env		*tmp;
	long long	exit_num;

	s = NULL;
	tmp = env;
	if (matrix[1] != NULL && (matrix[1][0] == '0' || \
			matrix[1][0] == '+' || matrix[1][1] == '0'))
		matrix[1] = trim_zeroes(matrix[1]);
	exit_num = ft_atll(matrix[1]);
	s = ft_itul(exit_num);
	if (matrix[1] && matrix[1][0] == '+')
		s = ft_strjoin("+", s, -1);
	if (matrixlen(matrix) == 1 && matrix[1] == NULL)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, "$?"))
				break ;
			tmp = tmp->next;
		}
		printf("exit\n");
		free_matrix(matrix);
		exit(ft_atoi(tmp->data));
	}
	else if (matrixlen(matrix) == 2 && ft_strcmp(s, matrix[1]) == 0)
	{
		ft_dprintf(2, "exit\n");
		free_matrix(matrix);
		if (exit_num == 0)
			exit (EXIT_SUCCESS);
		exit (exit_num % 256);
	}
	else if (ft_strlen(s) > 19 || check_digit(matrix[1]) == 1 || \
		ft_strcmp(s, matrix[1]) != 0)
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "Minishell: exit: %s: numeric argument required\n", \
			matrix[1]);
		free_matrix(matrix);
		free(s);
		exit(255);
	}
	else if (matrixlen(matrix) > 2 && check_digit(matrix[1]) == 0)
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "Minishell: exit: too many arguments\n");
		free_matrix(matrix);
	}
	if (s)
	{
		free(s);
		s = NULL;
	}
}
