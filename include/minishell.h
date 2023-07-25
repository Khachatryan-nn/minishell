/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/07/25 19:03:41 by tikhacha         ###   ########.fr       */
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
	int				flag;
	int				err_code;
	struct s_parser	*next;
	struct s_parser	*prev;
	struct s_parser	*left;
	struct s_parser	*right;
}					t_parser;

/*
	char		**path;
	t_parser	*pars;
	t_parser	*lex;
	t_parser	*temp;
*/
typedef struct s_init
{
	char		**path;
	t_parser	*pars;
	t_parser	*lex;
	t_parser	*temp;
}				t_init;

/* - - - - --!-- - - - - ! Handling spec tokens ! - - - - --!-- - - - - */
int			handle_prnthses(t_parser **res, char *line, int i, int count);
int			handle_squotes(t_parser **res, char *line, int i, int count);
int			handle_dquotes(t_parser **res, char *line, int i, int count);
int			handle_heredoc(t_parser **res, char *line, int i, int count);
int			handle_wappend(t_parser **res, char *line, int i, int count);
int			handle_wtrunc(t_parser **res, char *line, int i, int count);
int			handle_input(t_parser **res, char *line, int i, int count);
void		handle_space(t_parser **res, char *line, int i, int count);
int			handle_pipe(t_parser **res, char *line, int i, int count);
int			handle_xand(t_parser **res, char *line, int i, int count);
int			handle_xor(t_parser **res, char *line, int i, int count);
const char	*get_token_name(t_type token);

/* - - - - - --!-- - - - - ! Nodes and lists ! - - - - --!-- - - - - - */
t_parser	*lstnew_pars(char *content, t_type type, int prec, int flag);
void		lstback(t_parser **lst, t_parser *new);
void		destroy_structure(t_parser *root);
void		destroy_init(t_init *init);
void		lstclear(t_parser **lst);
t_parser	*lstlast(t_parser *lst);
int			lstsize(t_parser *lst);
t_list		*ft_lstnew_2(char *str);

/* - - - - - --!-- - - - - ! Lexer and parser ! - - - - --!-- - - - - - */
int 		check_ast(t_init *init, t_parser *pars, t_list *env);
void		lex(char *line, t_init *init);
int			lexer(t_parser **res, char *line);
void		parser(t_init *init);

/* - - - - - --!-- - - - - - ! RPN and AST ! - - - - - --!-- - - - - - */
void		shunting_yard(t_parser **p, t_parser **ops, t_parser **otp);
t_parser	*abstract_syntax_tree(t_init *init, t_parser **stack);
void		print_ast(t_parser *ast, int indent, int lrc);
void		push(t_parser **a, t_parser **b);
void		pop(t_parser **stack);

/* - - - - - --!-- - - - - ! Utils and helpers ! - - - - --!-- - - - - - */
char		*strjoin_helper(char *result, char *read, int mode);
int			restore_cmd_line(t_parser *lex, char **str);
int			ft_isspace(char *line, int i, int j);
void		find_path(t_cmd *cmd, t_list *env);
int			check_cmd(t_cmd *cmd, t_list *env);
int			is_delitimer(t_parser *root);
int			parse_error(char *err_str);
void		print_types(t_parser *ptr);
int			ft_onlyspaces(char *str);
void		free_matrix(void **ptr);
int			is_valid(t_init *init);

/* - - - - - --!-- - - - - ! builtins handling ! - - - - --!-- - - - - - */
void		ft_export_change(char *line, t_list *env);
void		ft_create_env(char **str, t_list **stack);
void		ft_cd_prev(t_list *str, char *text);
int			check_built(char *str, t_list *env);
void		ft_unset(char *ptr, t_list *env);
void		ft_cd(t_list *str, char *ptr);
void		ft_export(t_list *env);
void		ft_pwd(t_list *env);
void		ft_env(t_list *env);
char		*ft_ls(char *str);

/* - - - - - --!-- - - - - ! etc. - et cetera ! - - - - --!-- - - - - - */

int			ft_list_change(t_list *new, t_list *env);
void		find_path(t_cmd *cmd, t_list *env);
char		*ft_find_symbol(char *str, char c);
int			check_cmd(t_cmd *cm, t_list *env);
int			ft_strcmp(char *s1, char *s2);
int			checker(t_cmd *cmd);

#endif