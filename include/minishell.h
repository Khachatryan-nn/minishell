/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/08/21 17:38:52 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_dprintf.h"
# include <dirent.h>

# ifndef ZSH
# 	define ZSH 0
# endif


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

//	@brief
//	@tparam char	*cmd_line
//	@tparam	char	*cmd_path
//	@tparam	char	**cmd_args
//	@tparam	char	**path
//	@tparam int		stdin
//	@tparam	int		stdout
//	@tparam	int		pipes[2]
typedef struct s_cmd
{
	int		*pipes;
	char	**cmd_args;
	char	*cmd_line;
	char	*cmd_path;
	char	**path;
	int		stdout;
	int		stdin;
}			t_cmd;

//	@brief
//	@tparam char		*cmd
//	@tparam	char		*rpath
//	@tparam	char		*lpath
//	@tparam	t_type		type
//	@tparam int			prc
//	@tparam	int			flag
//	@tparam	int			err_code
//	@tparam	int			(*pipes)[2]
//	@tparam	s_parser	*next
//	@tparam	s_parser	*prev
//	@tparam	s_parser	*left
//	@tparam	s_parser	*right
typedef struct s_parser
{
	char			*cmd;
	char			*rpath;
	char			*lpath;
	t_type			type;
	int				prc;
	int				flag;
	int				subshell_code;
	int				err_code;
	int				pipes[2];
	struct s_parser	*next;
	struct s_parser	*prev;
	struct s_parser	*left;
	struct s_parser	*right;
}					t_parser;

//	@brief
//	@tparam int			exit_status
//	@tparam	char		**path
//	@tparam	int			flag
//	@tparam	t_parser	*pars
//	@tparam	t_parser	*lex
//	@tparam	t_parser	*temp
typedef struct s_init
{
	int			exit_status;
	char		**path;
	int			flag;
	t_parser	*pars;
	t_parser	*lex;
	t_parser	*temp;
}				t_init;

/* - - - - --!-- - - - - ! Handling spec tokens ! - - - - --!-- - - - - */
int			handle_prnthses(t_parser **res, char *line, int i, int count);
int			handle_squotes(t_parser **res, char **line, int i, int count);
int			handle_dquotes(t_parser **res, char **line, int i, int count);
int			handle_heredoc(t_parser **res, char *line, int i, int count);
int			handle_wappend(t_parser **res, char *line, int i, int count);
int			handle_wtrunc(t_parser **res, char *line, int i, int count);
int			handle_input(t_parser **res, char *line, int i, int count);
void		handle_space(t_parser **res, char *line, int i, int count);
int			handle_pipe(t_parser **res, char *line, int i, int count);
int			handle_xand(t_parser **res, char *line, int i, int count);
int			handle_xor(t_parser **res, char *line, int i, int count);
void		heredoc_input(char	*limiter, t_parser **res);
const char	*get_token_name(t_type token);

/* - - - - - --!-- - - - - ! Nodes and lists ! - - - - --!-- - - - - - */
t_parser	*lstnew_pars(char *content, t_type type, int prec, int flag);
void		lstback(t_parser **lst, t_parser *new);
void		destroy_structure(t_parser *root);
void		destroy_init(t_init *init);
void		lstclear(t_parser **lst);
t_list		*ft_lstnew_2(char *str);
t_parser	*lstlast(t_parser *lst);
int			lstsize(t_parser *lst);

/* - - - - - --!-- - - - - ! Lexer and parser ! - - - - --!-- - - - - - */
int			handle_cprnthses(t_parser **res, char *line, int i, int count);
int			add_new_quote(t_parser **res, char *line, int i, int type);
int 		check_ast(t_init *init, t_parser *pars, t_list *env);
int			lexer(t_parser **res, char **line);
void		lex(char **line, t_init *init);
int			check_type(t_type type);
void		parser(t_init *init);

/* - - - - - --!-- - - - - - ! RPN and AST ! - - - - - --!-- - - - - - */
void		shunting_yard(t_parser **p, t_parser **ops, t_parser **otp);
t_parser	*abstract_syntax_tree(t_init *init, t_parser **stack);
void		print_ast(t_parser *ast, int indent, int lrc);
void		push(t_parser **a, t_parser **b);
void		pop(t_parser **stack);

/* - - - - - --!-- - - - - - - ! Executer ! - - - - - --!-- - - - - - - */
int			to_execute(t_parser *pars, t_list *env, t_init *init, int status);
int			subsh_execute(t_parser *pars, t_list *env, t_init *init, int pid);
int			pipe_prepair(t_init *init, t_parser *pars, t_list *env);
int			exec_iocmd(t_init *init, t_parser *stack, t_list *env);
int			call_cmd(t_parser *stack, t_init *init, t_list *env);
char		**restore_cmd_line(t_parser *stack);
char		*check_cmd(char *cmd, char **path);
char		**env_matrix(t_list *env);
int			error_code(int error_num);

/* - - - - - --!-- - - - - ! Utils and helpers ! - - - - --!-- - - - - - */
char		*strjoin_helper(char *result, char *read, int mode);
int			ft_isspace(char *line, int i, int j);
void		find_path(t_init *init, t_list *env);
int			parse_error(char *err_str, int mode);
int			is_delimiter(t_parser *root);
void		print_types(t_parser *ptr);
int			ft_onlyspaces(char *str);
void		free_matrix(char **ptr);
int			is_valid(t_init *init);
void		close_pipes(int *fd);

/* - - - - - --!-- - - - - ! builtins handling ! - - - - --!-- - - - - - */
void		ft_export_change(char *line, t_list *env, t_init *init);
char		**ft_change_2(char *str);
void		ft_create_env(char **str, t_list **stack);
int			check_built(t_parser *stack, t_list *env, t_init *init);
void		ft_unset(char *ptr, t_list *env, t_init *init);
void		ft_cd(t_list *str, char **ptr);
void		ft_export(t_list *env);
char		**ft_export_continue(t_list *env1);
char		**ft_export_continue2(t_list *env, t_list *env1, char **ptr, int a);
void		ft_pwd(t_list *env);
void		ft_env(t_list *env);
void		ft_echo(t_list *env, t_init *init);
void		ft_echo_dollar(char *str, t_list *env);
void		ft_check_echo_env(char *str, t_list *env);
void		ft_exit(t_list *env, t_init *init);
void		exit_env(int a, t_list *env);
int			ft_atoi_2(long long a);
void		ft_check_valid(char *str, t_list *env);
void		ft_check_valid_2(char *str, t_list *env);
void		ft_check_valid_3(t_init *lst, t_list *env);
void		ft_find_env_echo(t_list *env);
char		*ft_expand(char *str, t_list *env);
char		*expand_change(char *str, int i, t_list *env);
char		*ft_kes(char *str, int i, t_list *env);
char		*ft_kes_2(char *ptr, char *ttr, char *str);

/* - - - - - --!-- - - - - ! etc. - et cetera ! - - - - --!-- - - - - - */

int			ft_list_change(t_list *new, t_list *env, t_init *init);
char		*ft_find_symbol(char *str, char c);
int			ft_strcmp(char *s1, char *s2);


/*   avelacvac  */
void	ft_check_main(char *str, t_list env, t_init init);
void	ft_handle(int signal);
void	ft_signal();
#endif