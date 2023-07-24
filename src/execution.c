#include "minishell.h"

int check_ast(t_init *init, t_parser *pars, t_list *env);

int check_ast(t_init *init, t_parser *pars, t_list *env)
{
	if (pars->left == NULL && pars->right == NULL)
		check_built(pars->cmd, env);
	if (pars->left != NULL)
		check_ast(init, pars->left, env);
	if (pars->right != NULL)
		check_ast(init, pars->right, env);
	return (0);
}