/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:45:02 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/10 20:25:12 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_types(t_tok *ptr);
int			parse_error(char *err_str, int mode);

int	parse_error(char *err_str, int mode)
{
	if (err_str[0] == '(')
		ft_dprintf(2, "minishell: syntax error missing token `%s'\n", ")");
	else
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n", \
		err_str);
	if (mode)
		free (err_str);
	return (0);
}

void	print_types(t_tok *ptr)
{
	if (!ptr)
		printf("%p", NULL);
	while (ptr)
	{
		if (ptr->next != NULL)
			printf("%s [%d] ", ptr->cmd, ptr->flag & (_SUBSH_));
		else
			printf("%s [%d]", ptr->cmd, ptr->flag & (_SUBSH_));
		ptr = ptr->next;
	}
	printf("\n");
}
