/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/07/19 20:33:45 by tikhacha         ###   ########.fr       */
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


typedef enum e_token_type
{
	WORD,			//	cmd
	DQUOTE_OPEN,	//	"
	DQUOTE_CLOSE,	//	"
	SQUOTE_OPEN,	//	'
	SQUOTE_CLOSE,	//	'
	SUBSH_OPEN,		//	(
	SUBSH_CLOSE,	//	)
	XOR,			//	||
	XAND,			//	&&
	PIPE,			//	|
	HEREDOC,		//	<<
	WRITE_APPEND,	//	>>
	WRITE_TRUNC,	//	>
	FILEIN,			//	fname
	FILEOUT,		//	fname
	END,			//	end of cmd
}	t_type;

/*
	char	*cmd_line;
	char	*cmd_path;
	char	**cmd_args;
	char	**path;
	int		stdin;
	int		stdout;
*/
typedef struct s_cmd
{
	char	*cmd_line;
	char	*cmd_path;
	char	**cmd_args;
	char	**path;
	int		stdin;
	int		stdout;
}			t_cmd;

/*
	char		*cmd;
	t_type		type;
	t_lexargs	*next;
*/
typedef struct s_lexer_arg
{
	char				*cmd;
	t_type				type;
	struct s_lexer_arg	*next;
}						t_lexargs;

/*
	char		*cmd;
	t_type		type;
	t_parser	*next;
	t_parser	*prev;
	t_parser	*left;
	t_parser	*right;
*/
typedef struct s_parser
{
	char			*cmd;
	t_type			type;
	struct s_parser	*next;
	struct s_parser	*prev;
	struct s_parser	*left;
	struct s_parser	*right;
}					t_parser;

/*
	char		**path;
	t_parser	*pars;
	t_lexargs	*lex;
*/
typedef struct s_init
{
	char		**path;
	t_parser	*pars;
	t_lexargs	*lex;
}				t_init;

/* - - - - --!-- - - - - ! Handling characters ! - - - - --!-- - - - - */
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
const char	*get_token_name(t_type token);

/* - - - - - --!-- - - - - ! Nodes and lists ! - - - - --!-- - - - - - */
void		ft_lstadd_back_3(t_lexargs **lst, t_lexargs *new);
void		lstadd_back_pars(t_parser **lst, t_parser *new);
t_lexargs	*ft_lstnew_3(char *content, t_type type);
t_parser	*lstnew_pars(char *content, t_type type);
void		ft_lstclear_3(t_lexargs **lst);
t_lexargs	*ft_lstlast_3(t_lexargs *lst);
void		lstclear_pars(t_parser **lst);
t_parser	*lstlast_pars(t_parser *lst);
void		destroy_init(t_init *init);
t_list		*ft_lstnew_2(char *str);

/* - - - - - --!-- - - - - ! Lexer and parser ! - - - - --!-- - - - - - */
void		lex(char *line, t_list *env, t_init *init);
int			lexer(t_lexargs **res, char *line);
void		parser(t_list *env, t_init *init);

/* - - - - - --!-- - - - - ! Utils and helpers ! - - - - --!-- - - - - - */
int			restore_cmd_line(t_lexargs *lex, char **str);
void		strjoin_helper(char *read, char *result);
int			ft_isspace(char *line, int i, int j);
void		find_path(t_cmd *cmd, t_list *env);
int			parse_error(char *err_str);
void		print_types(t_init *init);
int			ft_onlyspaces(char *str);
void		free_matrix(void **ptr);
int			is_valid(t_init *init);

/* - - - - - --!-- - - - - ! etc. - et cetera ! - - - - --!-- - - - - - */
int			check_cmd(t_cmd *cmd);
int			checker(t_cmd *cmd);
void		find_path(t_cmd *cmd, t_list *env);
void		ft_pwd(t_list *env);
void		ft_create_env(char **str, t_list **stack);
void		ft_env(t_list *env);
void		ft_cd(t_list *str, char *text);
// char    *ft_change_str(char *str);
char		*ft_find_symbol(char *str, char c);
void		ft_cd_prev(t_list *str, char *text);
char		*ft_ls(char *str);
// char		*read_line(const char *str);

#endif
