/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:17:48 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/25 16:46:36 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_list *str, char *ptr)
{
	t_list	*env;
	t_list	*env1;
	t_list	*start;
	char	*text;
	char	*text1;

	(void) str;
	(void) env;
	(void) env1;
	(void) start;
	(void) text1;
	text = NULL;
	text1 = NULL;
	text = ptr;
	env = NULL;
	env1 = NULL;
	start = NULL;
	while (*text == ' ' && *text)
		text++;
	while (*text != ' ' && *text)
		text++;
	while (*text == ' ' && *text)
		text++;
	text1 = getcwd(NULL, 0);
	if (chdir(text) == 0)
		;
	else
		perror("minishell");

}