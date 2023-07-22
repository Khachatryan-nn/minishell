/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:25:02 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/22 22:54:31 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_list *env)
{
	char *ptr;

	(void)env;
	ptr = NULL;
	ptr = getcwd(NULL, 0);
	printf("%s\n", ptr);
	free (ptr);
}
