/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:45:52 by tikhacha          #+#    #+#             */
/*   Updated: 2023/06/18 02:03:53 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_cmd
{
	char	**path;
	char	*cmd_line;
	char	**cmd_args;
	int		stdin;
	int		stdout;
}			t_cmd;

typedef struct s_lexer_arg
{
	char	*cmd;
	void	*next;
}			t_lexargs;

# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "minishell.h"

char	*get_next_line(int fd);

#endif
