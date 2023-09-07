/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:56:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/07 13:31:48 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_exit_status(t_tok *stack, char **matrix, char *s, int exit_num);
int		mshell_exit(t_tok *stack, char **matrix, t_env *env, char *s);
int		exit_error_code(t_tok *stack, t_env *env, char *s);
char	*check_zeroes(char *str);

int	mshell_exit(t_tok *stack, char **matrix, t_env *env, char *s)
{
	long long	exit_num;

	if (matrix[1] != NULL)
		matrix[1] = check_zeroes(matrix[1]);
	exit_num = ft_atll(matrix[1]);
	s = ft_itul(exit_num);
	if (matrix[1] && matrix[1][0] == '+' && matrix[1][0] == '-')
	{
		if (matrix[1][0] == '+')
			s = ft_strjoin("+", s, 2);
		else if (matrix[1][0] == '-')
			s = ft_strjoin("-", s, 2);
	}
	if (matrixlen(matrix) == 1 && matrix[1] == NULL)
		return (exit_error_code(stack, env, s));
	exit_num = check_exit_status(stack, matrix, s, exit_num);
	if (exit_num == 1000)
		return (1);
	if (check_subsh(stack) || (stack->flag & _PIPES_))
		return (exit_num);
	exit (exit_num);
}

int	exit_error_code(t_tok *stack, t_env *env, char *s)
{
	t_env	*tmp;

	tmp = env;
	if (*s)
		free(s);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "$?"))
			break ;
		tmp = tmp->next;
	}
	if (check_subsh(stack) || (stack->flag & _PIPES_))
		return (ft_atoi(tmp->data));
	ft_dprintf(2, "exit\n");
	exit (ft_atoi(tmp->data));
}

int	check_exit_status(t_tok *stack, char **matrix, char *s, int exit_num)
{
	if (matrixlen(matrix) == 2 && ft_strcmp(s, matrix[1]) == 0)
	{
		if (!check_subsh(stack) && !(stack->flag & _PIPES_))
			ft_dprintf(2, "exit\n");
		free(s);
		return (exit_num % 256);
	}
	else if (ft_strlen(s) > 19 || check_digit(matrix[1]) == 1 || \
		ft_strcmp(s, matrix[1]) != 0)
	{
		ft_dprintf(2, "exit\nminishell: exit: %s: numeric argument required\n", \
			matrix[1]);
		free(s);
		return (255);
	}
	else if (matrixlen(matrix) > 2 && check_digit(matrix[1]) == 0)
	{
		ft_dprintf(2, "exit\nminishell: exit: too many arguments\n");
		free(s);
		return (1000);
	}
	free(s);
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
	tmp = ft_strdup(str);
	free(str);
	return (tmp);
}
