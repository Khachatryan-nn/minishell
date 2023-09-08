/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/09/09 02:49:14 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft.h"
# include "lexer.h"
# include "utils.h"
# include "defines.h"
# include "structs.h"
# include "executer.h"
# include "builtins.h"
# include "etc.h"
# include "ft_dprintf.h"
# include "get_next_line.h"

int	g_exit_status_;

#endif