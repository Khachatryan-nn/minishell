#include "minishell.h"

void	ft_handle(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	else if (signal == SIGQUIT)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal()
{
	signal(SIGINT, ft_handle);
	signal(SIGQUIT, ft_handle);
}