/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:31:55 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/05 22:56:49 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_error(char	*str, char *err);
int		error_code(int error_num);

int	error_code(int error_num)
{
	if (error_num == 256)
		return (1);
	return (error_num % 256);
}

void	builtins_error(char	*str, char *err)
{
	if (!ft_strcmp(str, "cd") && err == NULL)
		ft_dprintf(2, "cd: error retrieving current directory: %s%s\n", \
					"getcwd: cannot access parent directories: ", \
					"No such file or directory");
	else if (!ft_strcmp(str, "export") && err)
		ft_dprintf(2, "Minishell: export: `%s': not a %s\n", \
					err, "valid identifier");
	else if (!ft_strcmp(str, "unset") && err)
		ft_dprintf(2, "Minishell: unset: `%s': not a %s\n", \
					err, "valid identifier");
}
