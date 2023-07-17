/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:45:02 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/16 02:13:54 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char static	*ft_strjoin_ws(char const *s1, char const *s2);
int	restore_cmd_line(t_lexargs *lex, char **str);

char static	*ft_strjoin_ws(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len_s1 + 1);
	ft_strlcat(ptr, " ", len_s1 + 2);
	ft_strlcat(ptr, s2, len_s1 + len_s2 + 2);
	return (ptr);
}

int	restore_cmd_line(t_lexargs *lex, char **str)
{
	char *temp;

	temp = *str;
	if (lex->type != WORD)
		return (0);
	else if (*str == NULL)
		*str = lex->cmd;
	else
	{
		*str = ft_strjoin_ws(*str, lex->cmd);
		free(temp);
	}
	return (1);
}
