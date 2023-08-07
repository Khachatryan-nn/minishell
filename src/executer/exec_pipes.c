/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:34:10 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/03 17:23:14 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_prepair(t_parser *pars);

int	pipe_prepair(t_parser *pars)
{
	pars->left->flag += 1 << 5;
	pars->right->flag += 1 << 5;
	if (pipe(pars->pipes) == -1)
	{
		pars->err_code = 1;
		perror("minishell");
		return (1);
	}
	return (0);
}
//	xxxxxx1 -> command
//	xxxxx1x -> space
//	xxxx1xx -> executed or not (???)
//	xxx1xxx -> command for I/O
//	xx1xxxx -> arg for I/O
//	x1xxxxx -> pipe child
//	1xxxxxx -> subsh first cmd

//	1 << 0 -> 0000001 -> 1	| cmd
//	1 << 1 -> 0000010 -> 2	| space
//	1 << 2 -> 0000100 -> 4	| exec stat
//	1 << 3 -> 0001000 -> 8	| I/O
//	1 << 4 -> 0010000 -> 16	| I/O arg
//	1 << 5 -> 0100000 -> 32	| PIPE childs
//	1 << 6 -> 1000000 -> 64 | SUBSH first command
//	1111111 -> 127