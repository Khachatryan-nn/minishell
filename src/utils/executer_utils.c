/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:58:53 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/18 22:56:28 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar(int exit_status, t_env *env);
void	save_backup(t_init *init);
int		check_subsh(t_tok *stack);
char	**env_matrix(t_env *env);

char	**env_matrix(t_env *env)
{
	char	**n_env;
	t_env	*ptr;
	int		i;

	ptr = env;
	i = 0;
	n_env = (char **)malloc(sizeof(char *) * (env_lstsize(env) + 1));
	while (ptr)
	{
		if (!ptr->flag)
		{
			n_env[i] = ft_strdup(ptr->key);
			n_env[i] = ft_strjoin(n_env[i], "=", 1);
			n_env[i] = ft_strjoin(n_env[i], ptr->data, 1);
			i++;
		}
		ptr = ptr->next;
	}
	n_env[i] = NULL;
	return (n_env);
}

void	handle_dollar(int exit_status, t_env *env)
{
	t_env	*tmp;
	char	*status;

	tmp = env;
	status = ft_itoa(exit_status);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "$?"))
		{
			free(tmp->data);
			tmp->data = ft_strdup(status);
			break ;
		}
		tmp = tmp->next;
	}
	g_exit_status_ = 0;
	free(status);
}

void	save_backup(t_init *init)
{
	init->stdin_backup = dup(STDIN_FILENO);
	if (init->stdin_backup == -1)
		perror("minishell");
	init->stdout_backup = dup(STDOUT_FILENO);
	if (init->stdout_backup == -1)
		perror("minishell");
}

int	check_subsh(t_tok *stack)
{
	t_tok	*temp;

	temp = stack;
	while (temp)
	{
		if (temp->sub)
			return (1);
		temp = temp->next;
	}
	return (0);
}
