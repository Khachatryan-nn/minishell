/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:34:01 by musimony          #+#    #+#             */
/*   Updated: 2023/09/05 22:54:07 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "ft_dprintf.h"
# include "get_next_line.h"
# include <readline/history.h>
# include <readline/readline.h>

# define _CD_		"cd"
# define _PWD_		"pwd"
# define _ENV_		"env"
# define _EXIT_		"exit"
# define _ECHO_		"echo"
# define _UNSET_	"unset"
# define _EXPORT_	"export"

# define _ISCMD_	1 << 1
# define _REDIR_	1 << 3
# define _PIPES_	1 << 5
# define _SUBSH_	1 << 6

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
	WR_APPEND,
	WR_TRUNC,
	INPUT,
	FILEIN,
	FILEOUT,
	END,
}	t_type;

/// @brief 
///	@tparam int		i;
///	@tparam int		l;
///	@tparam char	*s;
///	@tparam char	*str;
typedef struct s_exp
{
	int		i;
	int		l;
	char	*str;
	char	*s;
}			t_exp;

/// @brief 
///	@tparam char	**fn;
///	@tparam int		i;
typedef	struct s_hd
{
	char	**fn;
	int		i;
}			t_hd;

///	@brief
///	@tparam	struct s_env	*next
///	@tparam	struct s_env	*prev
///	@tparam	char			*data
///	@tparam	char			*key
///	@tparam	char			*pwd
///	@tparam	int				flag
typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*data;
	char			*key;
	char			*pwd;
	int				flag;
}					t_env;


///	@brief
///	@tparam char	*cmd_line
///	@tparam	char	*cmd_path
///	@tparam	char	**cmd_args
///	@tparam	char	**path
///	@tparam int		stdin
///	@tparam	int		stdout
///	@tparam	int		pipes[2]
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

///	@brief
///	@tparam	int				fd
///	@tparam	int				prc
///	@tparam	char			*cmd
///	@tparam	t_type			type
///	@tparam	int				flag
///	@tparam	struct s_tok	*next
///	@tparam	struct s_tok	*prev
///	@tparam	struct s_tok	*left
///	@tparam	struct s_tok	*right
///	@tparam	int				_stdin_
///	@tparam	int				pipes[2]
///	@tparam	int				_stdout_
///	@tparam	int				err_code
///	@tparam	int				last_red
///	@tparam	int				last_hdoc
///	@tparam	int				last_input
///	@tparam	char			*hdoc_fname
///	@tparam	int				stdin_backup
///	@tparam	int				subshell_code
///	@tparam	int				stdout_backup
typedef struct s_tok
{
	int				fd;
	int				prc;
	char			*cmd;
	t_type			type;
	int				flag;
	struct s_tok	*next;
	struct s_tok	*prev;
	struct s_tok	*left;
	struct s_tok	*right;
	int				_stdin_;
	int				pipes[2];
	int				_stdout_;
	int				err_code;
	int				last_red;
	int				last_hdoc;
	int				last_input;
	char			*hdoc_fname;
	int				stdin_backup;
	int				subshell_code;
	int				stdout_backup;
}					t_tok;

///	@brief
///	@tparam t_hd	*hd
///	@tparam	int		hdoc
///	@tparam	int		flag
///	@tparam	t_tok	*lex
///	@tparam	t_tok	*pars
///	@tparam	t_tok	*temp
///	@tparam int		input
///	@tparam	int		redir
///	@tparam	char	**path
///	@tparam	int		fd_fail;
///	@tparam	int		last_hdoc
///	@tparam	int		last_redir
///	@tparam	int		last_input
///	@tparam int		exit_status
///	@tparam	int		stdin_backup
///	@tparam	int		stdout_backup
typedef struct s_init
{
	t_hd	*hd;
	int		hdoc;
	int		flag;
	t_tok	*lex;
	t_tok	*pars;
	t_tok	*temp;
	int		input;
	int		redir;
	char	**path;
	int		fd_fail;
	int		last_hdoc;
	int		last_redir;
	int		last_input;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}			t_init;

///	@brief 
///	@tparam	s_wcard		*next
///	@tparam	s_wcard		*prev
///	@tparam	char		*file
typedef struct s_wcard
{
	struct s_wcard		*next;
	struct s_wcard		*prev;
	char				*file;
}						t_wcard;

/* - - - - --!-- - - - - ! Handling spec tokens ! - - - - --!-- - - - - */
int			handle_prnthses(t_tok **res, char *line, int i, int count);
int			handle_squotes(t_tok **res, char **line, int i, int count);
int			handle_dquotes(t_tok **res, char **line, int i, int count);
int			handle_heredoc(t_tok **res, char *line, int i, int count);
int			handle_wappend(t_tok **res, char *line, int i, int count);
int			handle_wtrunc(t_tok **res, char *line, int i, int count);
int			handle_input(t_tok **res, char *line, int i, int count);
void		handle_space(t_tok **res, char *line, int i, int count);
int			handle_pipe(t_tok **res, char *line, int i, int count);
int			handle_xand(t_tok **res, char *line, int i, int count);
int			handle_xor(t_tok **res, char *line, int i, int count);
const char	*get_token_name(t_type token);
char		*heredoc_input(char	*limiter);

/* - - - - - --!-- - - - - ! Nodes and lists ! - - - - --!-- - - - - - */
t_tok		*lstnew_pars(char *content, t_type type, int prec, int flag);
void		lstback_wcard(t_wcard **pars, t_wcard *new);
t_env		*push_back(t_env **list, t_env *new);
void		lstback(t_tok **lst, t_tok *new);
void		destroy_structure(t_tok *root);
void		lstclear_wcard(t_wcard **lst);
t_wcard		*lstlast_wcard(t_wcard *lst);
t_wcard		*lstadd_wcard(char *string);
int			lstsize_wcard(t_wcard *lst);
void		destroy_init(t_init *init);
t_tok		*ast_branch(t_tok *tok);
t_env		*malloc_list(char *env);
int			env_lstsize(t_env *lst);
void		lstclear(t_tok **lst);
t_tok		*lstlast(t_tok *lst);
int			lstsize(t_tok *lst);

/* - - - - - --!-- - - - - ! Lexer and parser ! - - - - --!-- - - - - - */
int			handle_cprnthses(t_tok **res, char *line, int i, int count);
void		handle_heredoc_input(t_init *init, t_tok *tok, char *str);
int			add_new_quote(t_tok **res, char *line, int i, int type);
int 		check_ast(t_init *init, t_tok *root, t_env *env);
int			lexer(t_tok **res, char **line);
char		*rem_lim_quotes(char *limiter);
void		lex(char **line, t_init *init);
int			quote_count(char *limiter);
int			check_type(t_type type);
void		parser(t_init *init);

/* - - - - - --!-- - - - - - ! RPN and AST ! - - - - - --!-- - - - - - */
void		shunting_yard(t_tok **p, t_tok **ops, t_tok **otp);
t_tok		*abstract_syntax_tree(t_init *init, t_tok **stack);
void		print_ast(t_tok *ast, int indent, int lrc);
void		push(t_tok **a, t_tok **b);
void		pop(t_tok **stack);

/* - - - - - --!-- - - - - - - ! Executer ! - - - - - --!-- - - - - - - */
char		**alloc_cmd_matrix(char **matrix, char *cmd, t_wcard *wild, int *i);
char		**alloc_wc_matrix(char **matrix, t_tok *stack, t_wcard **wcard);
void		wcard_logic_2(char **pattern, char **string, int star);
int			pipe_prepair(t_init *init, t_tok *stack, t_env *env);
int			to_execute(t_init *init, t_tok *stack, t_env *env);
int			exec_iocmd(t_init *init, t_tok *stack, t_env *env);
void		check_lasts(t_init *init, t_tok *stack, int mode);
int			call_cmd(t_init *init, t_tok *stack, t_env *env);
int			io_backup(int stdin_backup, int stdout_backup);
void		fill_wc_matrix(t_tok *stack, t_wcard **wild);
void		handle_dollar(int exit_status, t_env *env);
int			wcard_logic(char *pattern, char *string);
char		**restore_cmd_line(t_tok *stack, int i);
void		get_file(char *path, t_wcard **wcard);
char		*check_cmd(char *cmd, char **path);
int			io_dup2(int _stdin, int _stdout);
int			error_code(int error_num);
char		**env_matrix(t_env *env);

/* - - - - - --!-- - - - - ! builtins handling ! - - - - --!-- - - - - - */
int			check_exit_status(char **arr, char *s, int exit_num);
void		mshell_exit(char **arr, t_env *env, char *s);
void		pwd_init_2(t_env *my_env, char *str, int *i);
void		mshell_export(char **matrix, t_env *my_env);
void		export(char **matrix, int i, t_env *my_env);
int			mshell_unset(char **matrix, t_env *my_env);
void		mshell_cd(char **matrix, t_env *my_env);
int			check_built(t_tok *stack, t_env *env);
t_env		*env_init(char **env, t_env *my_env);
int			ft_check(t_env *my_env, char *str);
void		mshell_pwd(char *str, t_env *env);
void		ft_add(t_env *my_env, char *str);
int			exit_error_code(t_env *env);
void		mshell_echo(char **matrix);
void		ft_export(t_env *my_env);
void		pwd_init(t_env *my_env);
int			check_unset(char *str);
void		mshell_env(t_env *env);
void		handler_stp(int sig);
void		call_signals(void);

/* - - - - - --!-- - - - - ! Utils and helpers ! - - - - --!-- - - - - - */
int			destroy_cmd(char *cmd, char **cmd_matrix, char **env_matrix);
char		*strjoin_helper(char *result, char *read, int mode);
int			find_limiter_end(char *line, int i, int start);
int			_free3_(char *ptr1, char **ptr2, char **ptr3);
int			ft_isspace(char *line, int i, int j);
int			parse_error(char *err_str, int mode);
void		builtins_error(char	*str, char *err);
int			_close3_(int fd1, int fd2, int fd3);
void		find_path(t_init *init, t_env *env);
unsigned long long int	ft_atll(char *str);
int			_close2_(int fd1, int fd2);
int			is_delimiter(t_tok *root);
void		save_backup(t_init *init);
int			ft_onlyspaces(char *str);
int			matrixlen(char **matrix);
void		print_types(t_tok *ptr);
const char	*token_is(t_type token);
void		free_matrix(char **ptr);
t_type		token_name(char *token);
int			check_digit(char *str);
int			is_valid(t_init *init);
char		*ft_itul(long long n);
char		*trim_zeroes(char *s);
int			close_pipes(int *fd);
void		init_hd(t_hd **hd);
int			_close_(int	fd);

/* - - - - - - --!-- - - - - - ! Expander ! - - - - - --!-- - - - - - - */
char		*expand(char *str, t_env *env, t_exp *exp);
void		do_expand(t_tok *stack, t_env *env);
void		exp_2(t_exp **tmp, t_env *env);
void		destroy_exp(t_exp *exp);
int			onlydollar(char *str);
void		exp_1(t_exp **tmp);
void		exp_3(t_exp **tmp);

/* - - - - - --!-- - - - - ! etc. - et cetera ! - - - - --!-- - - - - - */

int			ft_strcmp(char *s1, char *s2);
void		leaks_check(void);

#endif