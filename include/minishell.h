/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/07/07 20:04:38 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include <dirent.h>

// typedef struct dirent
// {
//     char *d_name;
// }   DIR;

typedef enum e_token_type
{
	WORD,
	DQUOTE_OPEN,
	DQUOTE_CLOSE,
	SQUOTE_OPEN,
	SQUOTE_CLOSE,
	SUBSH_OPEN,
	SUBSH_CLOSE,
	MATH_OPEN,
	MATH_CLOSE,
	XOR,
	XAND,
	PIPE,
	HEREDOC,
	REDIREC,
	WRITE_APPEND,
	WRITE_TRUNC,
	FILEIN,
	FILEOUT,
	VAR,
	COMMENT,
	CMD,
}		t_type;

// typedef struct s_list
// {
// 	char	*ptr;
// 	char	*value;
// 	void	*next;
// 	void	*prev;
// 	void	*content;
// }			t_list;

/*
	char	**path;
	char	*cmd_line;
	char	*cmd_path;
	char	**cmd_args;
	int		stdin;
	int		stdout;
*/
typedef struct s_cmd
{
	char	**path;
	char	*cmd_line;
	char	*cmd_path;
	char	**cmd_args;
	int		stdin;
	int		stdout;
}			t_cmd;

typedef struct s_lexer_arg
{
	char	*cmd;
	t_type	type;
	void	*next;
}				t_lexargs;

int			handle_prnthses(t_lexargs **res, char *line, int i, int count);
int			handle_squotes(t_lexargs **res, char *line, int i, int count);
int			handle_dquotes(t_lexargs **res, char *line, int i, int count);
int			handle_heredoc(t_lexargs **res, char *line, int i, int count);
int			handle_wappend(t_lexargs **res, char *line, int i, int count);
int			handle_wtrunc(t_lexargs **res, char *line, int i, int count);
void		handle_space(t_lexargs **res, char *line, int i, int count);
int			handle_pipe(t_lexargs **res, char *line, int i, int count);
int			handle_xand(t_lexargs **res, char *line, int i, int count);
int			handle_xor(t_lexargs **res, char *line, int i, int count);
int			handle_and(t_lexargs **res, char *line, int i, int count);
void		ft_lstadd_back_3(t_lexargs **lst, t_lexargs *new);
void		strjoin_helper(char *read, char *result);
int			ft_isspace(char *line, int i, int j);
void		find_path(t_cmd *cmd, t_list *env);
void		ft_lstclear_3(t_lexargs **lst);
const char	*get_token_name(t_type token);
void		lex(char *line, t_list *env);
int			ft_onlyspaces(char *str);
void		free_matrix(void **ptr);
int			check_cmd(t_cmd *cmd);
int			checker(t_cmd *cmd);
void		lexer(t_lexargs **res, char *line);
void		find_path(t_cmd *cmd, t_list *env);
t_lexargs	*ft_lstlast_3(t_lexargs *lst);
t_lexargs	*ft_lstnew_3(char *content, t_type type);
void		ft_pwd(t_list *env);
void		ft_create_env(char **str, t_list **stack);
void		ft_env(t_list *env);
t_list		*ft_lstnew_2(char *str);
void		ft_cd(t_list *str, char *text);
// char    *ft_change_str(char *str);
char		*ft_find_symbol(char *str, char c);
void		ft_cd_prev(t_list *str, char *text);
char		*ft_ls(char *str);
// char		*read_line(const char *str);

#endif
