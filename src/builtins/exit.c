/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:56:45 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/26 11:03:51 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_exit_status(t_tok *stack, char **matrix, char *s, int exit_num);
int		mshell_exit(t_tok *stack, char **matrix, t_env *env, char *s);
int		exit_error_code(t_tok *stack, t_env *env, char *s);
char	*num_sign(char *s, char c);
char	*check_zeroes(char *str);

int	mshell_exit(t_tok *stack, char **matrix, t_env *env, char *s)
{
	long long	exit_num;
	char		*str;

	if (matrixlen(matrix) == 1 && matrix[1] == NULL)
		return (exit_error_code(stack, env, s));
	if (matrix[1] != NULL)
		matrix[1] = check_zeroes(matrix[1]);
	exit_num = ft_atll(matrix[1]);
	s = ft_itul(exit_num);
	if (matrix[1] && matrix[1][0] == '+')
		str = num_sign(s, matrix[1][0]);
	else
	{
		str = ft_strdup(s);
		free (s);
	}
	exit_num = check_exit_status(stack, matrix, str, exit_num);
	free(str);
	if (exit_num == 1000)
		return (1000);
	if (check_subsh(stack) || (stack->flag & _PIPES_))
		return (exit_num);
	exit (exit_num);
}

int	exit_error_code(t_tok *stack, t_env *env, char *s)
{
	t_env	*tmp;

	(void) s;
	tmp = env;
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
	if (!check_subsh(stack) && !(stack->flag & _PIPES_))
		ft_dprintf(2, "exit\n");
	if (matrixlen(matrix) == 2 && ft_strcmp(s, matrix[1]) == 0 \
								&& check_digit(matrix[1]) != 1)
	{
		if (!exit_num)
			return (0);
		return ((unsigned char) exit_num);
	}
	else if (ft_strlen(s) > 19 || check_digit(matrix[1]) == 1 || \
		ft_strcmp(s, matrix[1]) != 0)
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", \
			matrix[1]);
		return (255);
	}
	else if (matrixlen(matrix) > 2 && check_digit(matrix[1]) == 0)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
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
		free(str);
		str = trim_zeroes(tmp);
		if (tmp[0] == '+' || tmp[0] == '-')
			str = num_sign(str, tmp[0]);
		free(tmp);
		return (str);
	}
	tmp = ft_strdup(str);
	free(str);
	return (tmp);
}

char	*num_sign(char *s, char c)
{
	char	*str;

	str = ft_strdup(s);
	free (s);
	s = NULL;
	if (c == '+')
		s = ft_strjoin("+", str, 0);
	else if (c == '-')
		s = ft_strjoin("-", str, 0);
	free (str);
	return (s);
}
