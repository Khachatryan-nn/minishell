/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/06/22 21:40:53 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// typedef struct dirent
// {
//     char *d_name;
// }   DIR;

enum cmd_type
{
	word = 0;
	dquote;
	squote;
	subsh;
	math;
	redirection;
	variable;
	comment;
	control flow;
	command;
}

typedef struct s_list
{
    char *ptr;
    char *value;
    void *next;
    void *prev;
    void *content;
}   t_list;


typedef struct s_cmd
{
	char	**path;
	char	*cmd_line;
	char	*cmd_path;
	char	**cmd_args;
	int		stdin;
	int		stdout;
}			t_cmd;

/*
types:
0 - word
1 - dquote
2 - squote
3 - subsh
4 - math
5 - redirection
6 - variable
7 - comment
8 - control flow
9 - command
*/
typedef struct s_lexer_arg
{
	char	*cmd;
	int		type;
	void	*next;
}			t_lexargs;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include <dirent.h>

// char		**ft_split(const char *s, char c);
// int		ft_size_word(char const *s, char c, int i);
// char		*ft_substr(char const *s, unsigned int start, size_t len);
// size_t	ft_strlen(const char *str);
// char		*ft_strdup(const char *s1);
// int		ft_strcmp(const char *s1, const char *s2);
// int		chdir(const char *str);
int			handle_op_parentheses(t_lexargs **res, char *line, int i, int count);
int			handle_squotes(t_lexargs **res, char *line, int i, int count);
int			handle_dquotes(t_lexargs **res, char *line, int i, int count);
void		handle_space(t_lexargs **res, char *line, int i, int count);
void		ft_lstadd_back_3(t_lexargs **lst, t_lexargs *new);
void		lex(char *line, t_list *env, char **env1);
void		strjoin_helper(char *read, char *result);
int			ft_isspace(char *line, int i, int j);
void		find_path(t_cmd *cmd, t_list *env);
void		ft_lstclear_3(t_lexargs **lst);
int			ft_onlyspaces(char *str);
void		free_matrix(void **ptr);
int			check_cmd(t_cmd *cmd);
int			checker(t_cmd *cmd);
void		lexer(t_lexargs **res, char *line);
void		find_path(t_cmd *cmd, t_list *env);
t_lexargs	*ft_lstlast_3(t_lexargs *lst);
t_lexargs	*ft_lstnew_3(char *content);
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
