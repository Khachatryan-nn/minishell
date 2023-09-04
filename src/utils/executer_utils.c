/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:58:53 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/04 14:39:18 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_matrix(t_lst *env);
void	save_backup(t_init *init);
void	handle_dollar(int exit_status, t_lst **env);
void	handle_heredoc_input(t_init *init, t_tok *tok, char *str);

char	**env_matrix(t_lst *env)
{
	char	**tmp;
	t_lst	*ptr;
	int		i;

	ptr = env;
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (ptr)
	{
		if (ptr->ptr && ptr->value)
		{
			tmp[i] = ft_strjoin(ptr->ptr, ptr->value, 0);
			i++;
		}
		ptr = ptr->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	handle_heredoc_input(t_init *init, t_tok *tok, char *str)
{
	char	*res;

	res = NULL;
	tok->hdoc_fname = ft_strdup(init->hd->fn[++init->hd->i]);
	tok->fd = open(init->hd->fn[init->hd->i], O_RDWR | O_CREAT | O_TRUNC, 0655);
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, tok->next->cmd) == 0)
		{
			free(str);
			break ;
		}
		if (!res)
			res = ft_strdup(str);
		else
			res = strjoin_helper(res, str, 1);
		free(str);
	}
	if (res)
		res = ft_strjoin(res, "\n", 1);
	else
		res = ft_strdup("");
	write(tok->fd, res, ft_strlen(res));
	_close2_(tok->fd, _free3_(res, NULL, NULL) - 42);
}

void	handle_dollar(int exit_status, t_lst **env)
{
	t_lst	*tmp;
	char	*status;

	tmp = (*env);
	status = ft_itoa(exit_status);
	while (tmp)
	{
		if (!ft_strcmp(tmp->ptr, "$?"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(status);
			break ;
		}
		tmp = tmp->next;
	}
	free(status);
}

void	save_backup(t_init *init)
{
	init->stdin_backup = dup(STDIN_FILENO);
	if (init->stdin_backup == -1)
		perror("Minishell");
	init->stdout_backup = dup(STDOUT_FILENO);
	if (init->stdout_backup == -1)
		perror("Minishell");
}
