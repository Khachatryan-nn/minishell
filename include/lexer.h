/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:59:23 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/20 12:33:27 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "defines.h"
# include "parser.h"

/* ************************** ! Token handling ! ************************** */
int			handle_cprnthses(t_tok **res, char *line, int i, int count);
char		*handle_quotes(t_tok **res, char **line, int *i, int count);
int			handle_squotes(t_tok **res, char **line, int *i, int count);
int			handle_dquotes(t_tok **res, char **line, int *i, int count);
int			handle_prnthses(t_tok **res, char *line, int i, int count);
int			handle_heredoc(t_tok **res, char *line, int i, int count);
int			handle_wappend(t_tok **res, char *line, int i, int count);
int			handle_wtrunc(t_tok **res, char *line, int i, int count);
void		handle_space(t_tok **res, char *line, int i, int count);
int			handle_input(t_tok **res, char *line, int i, int count);
int			handle_pipe(t_tok **res, char *line, int i, int count);
int			handle_xand(t_tok **res, char *line, int i, int count);
int			handle_xor(t_tok **res, char *line, int i, int count);

/* ******************************* ! Lexer ! ******************************* */
int			add_new_quote(t_tok **res, char *line, int i, int type);
void		heredoc_validation(t_init *init, t_tok *tok);
void		lex(char **line, t_init *init, t_env *env);
int			find_limiter_end(char *line, int start);
int			ft_isspace(char *line, int i, int j);
void		push_redir(t_tok *to, t_tok *from);
int			lexer(t_tok **res, char **line);
int			quote_count(char *line, char c);
void		unlink_heredocs(t_init	*init);
const char	*get_token_name(t_type token);
void		find_limiter(t_init *init, t_tok *stack);
int			is_delimiter(t_tok *root);
int			ft_onlyspaces(char *str);
const char	*token_is(t_type token);
t_type		token_name(char *token);
int			check_type(t_type type);
void		pop_redir(t_tok *tok);

#endif
