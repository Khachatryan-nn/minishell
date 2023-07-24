/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:45:02 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/24 16:03:26 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char static	*ft_strjoin_ws(char const *s1, char const *s2);
int			restore_cmd_line(t_lexargs *lex, char **str);
void		print_types(t_parser *ptr);
int			parse_error(char *err_str);

int	parse_error(char *err_str)
{
	printf("minishell: parse error near `%s'\n", err_str);
	return (0);
}

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
	//printf("\033[38;5;54m[%d] --\ttype: %s\033[0m\n\tcmd: %s\n", \
	//	0, get_token_name(ptr->type), ptr->cmd);
	//if (ptr->left != NULL)
	//	printf("\t\x1b[38;2;252;78;3m[%d] --\ttype: %s -> LEFT BRANCH\x1b[0m\n\tcmd: %s\n", \
	//	1, get_token_name(ptr->left->type), ptr->left->cmd);
	//if (ptr->right != NULL)
	//	printf("\t\x1b[38;2;252;78;3m[%d] --\ttype: %s -> RIGHT BRANCH\x1b[0m\n\tcmd: %s\n", \
	//	2, get_token_name(ptr->right->type), ptr->right->cmd);
}
