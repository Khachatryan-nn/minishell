/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/07/23 20:22:26 by tikhacha         ###   ########.fr       */
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
	WORD,
	DQUOTE,
	SQUOTE,
	SUBSH_OPEN,
	SUBSH_CLOSE,
	XOR,
	XAND,
	PIPE,
	HEREDOC,
	WRITE_APPEND,
	WRITE_TRUNC,
	INPUT,
	FILEIN,
	FILEOUT,
	END,
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
	int			prc;
	t_lexargs	*next;
*/
typedef struct s_lexer_arg
{
	char				*cmd;
	t_type				type;
	int					prc;
	struct s_lexer_arg	*next;
	struct s_lexer_arg	*prev;
}						t_lexargs;

/*
	char		*cmd;
	t_type		type;
	int			prc;
	t_parser	*next;
	t_parser	*prev;
	t_parser	*left;
	t_parser	*right;
*/
typedef struct s_parser
{
	char			*cmd;
	t_type			type;
	int				prc;
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
int			handle_input(t_lexargs **res, char *line, int i, int count);
void		handle_space(t_lexargs **res, char *line, int i, int count);
int			handle_pipe(t_lexargs **res, char *line, int i, int count);
int			handle_xand(t_lexargs **res, char *line, int i, int count);
int			handle_xor(t_lexargs **res, char *line, int i, int count);
const char	*get_token_name(t_type token);

/* - - - - - --!-- - - - - ! Nodes and lists ! - - - - --!-- - - - - - */
t_parser	*lstnew_pars(char *content, t_type type, int prec);
t_lexargs	*lstnew_lex(char *content, t_type type, int prec);
void		lstback_lex(t_lexargs **lst, t_lexargs *new);
void		lstback_pars(t_parser **lst, t_parser *new);
void		lstclear_lex(t_lexargs **lst);
void		lstclear_pars(t_parser **lst);
t_lexargs	*lstlast_lex(t_lexargs *lst);
t_parser	*lstlast_pars(t_parser *lst);
int			lstsize_pars(t_parser *lst);
void		destroy_init(t_init *init);
t_list		*ft_lstnew_2(char *str);

/* - - - - - --!-- - - - - ! Lexer and parser ! - - - - --!-- - - - - - */
void		lex(char *line, t_list *env, t_init *init);
int			lexer(t_lexargs **res, char *line);
void		parser(t_list *env, t_init *init);

/* - - - - - --!-- - - - - - ! RPN and AST ! - - - - - --!-- - - - - - */
t_parser	*abstract_syntax_tree(t_init *init, t_parser **stack);
void		print_ast(t_parser *ast, int indent, int lrc);
void		push(t_parser **a, t_parser **b);
void		pop(t_parser **stack);

/* - - - - - --!-- - - - - ! Utils and helpers ! - - - - --!-- - - - - - */
char		*strjoin_helper(char *result, char *read, int mode);
int			restore_cmd_line(t_lexargs *lex, char **str);
int			ft_isspace(char *line, int i, int j);
void		find_path(t_cmd *cmd, t_list *env);
int			is_delitimer(t_lexargs *root);
int			parse_error(char *err_str);
void		print_types(t_parser *ptr);
int			ft_onlyspaces(char *str);
void		free_matrix(void **ptr);
int			check_cmd(t_cmd *cmd, t_list *env);
int			is_valid(t_init *init);

/* - - - - - --!-- - - - - ! etc. - et cetera ! - - - - --!-- - - - - - */
int			check_cmd(t_cmd *cm, t_list *env);
int			checker(t_cmd *cmd);
void		find_path(t_cmd *cmd, t_list *env);
void		ft_pwd(t_list *env);
void		ft_create_env(char **str, t_list **stack);
void		ft_env(t_list *env);
t_list		*ft_lstnew_2(char *str);
void		ft_cd(t_list *str, char *ptr);
char		*ft_find_symbol(char *str, char c);
void		ft_cd_prev(t_list *str, char *text);
char		*ft_ls(char *str);
void		ft_export(t_list *env);
int			ft_strcmp(char *s1, char *s2);
int			ft_list_change(t_list *new, t_list *env);
void		ft_unset(char *ptr, t_list *env);
int			check_built(char *str, t_list *env);
void		ft_export_change(char *line, t_list *env);

#endif
