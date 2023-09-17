/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:07:53 by tikhacha          #+#    #+#             */
/*   Updated: 2023/09/17 17:08:17 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

t_tok	*tree_end(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp);
t_tok	*tree_ops(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp);
t_tok	*tree_otp(t_init *init, t_tok **stack, t_tok *new, t_tok *tmp);
void	shunting_yard(t_tok **p, t_tok **ops, t_tok **otp);
t_tok	*abstract_syntax_tree(t_init *init, t_tok **stack);
int		check_ast(t_init *init, t_tok *root, t_env *env);
int		is_valid(t_init *init, t_env *env, int *sb);
void	print_ast(t_tok *ast, int indent, int lrc);
int		parse_error(char *err_str, int mode);
void	parser(t_init *init, t_env *env);
t_tok	*most_prev(t_tok	*stack);
void	push(t_tok **a, t_tok **b);
void	print_types(t_tok *ptr);
void	pop(t_tok **stack);

#endif
