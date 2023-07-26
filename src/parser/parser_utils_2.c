/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:45:02 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/26 18:57:29 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_types(t_parser *ptr);
int			parse_error(char *err_str);

int	parse_error(char *err_str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", err_str);
	return (0);
}

void	print_types(t_parser *ptr)
{
	if (!ptr)
		printf("%p", NULL);
	while (ptr)
	{
		if (ptr->next != NULL)
			printf("%s ", ptr->cmd);
		else
			printf("%s", ptr->cmd);
		ptr = ptr->next;
	}
	printf("\n");
}
