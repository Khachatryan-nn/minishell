/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:56:21 by tikhacha          #+#    #+#             */
/*   Updated: 2023/10/16 16:59:32 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define _ISCMD_	2
# define _REDIR_	8
# define _PIPES_	32
# define _SUBSH_	64
# define _CD_		"cd"
# define _PWD_		"pwd"
# define _ENV_		"env"
# define _EXIT_		"exit"
# define _ECHO_		"echo"
# define _UNSET_	"unset"
# define _EXPORT_	"export"

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
typedef struct s_hd
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
///	@tparam	int				sub
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
	int				sub;
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

#endif
