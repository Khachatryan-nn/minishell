/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:37:28 by tikhacha          #+#    #+#             */
/*   Updated: 2023/07/24 12:24:26 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*abstract_syntax_tree(t_init *init, t_parser **stack);
void		print_ast(t_parser *ast, int indent, int lrc);

void	print_ast(t_parser *ast, int indent, int lrc)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
    print_ast(ast->right, indent + 1, 1);
	while (i++ < indent)
	{
        //if (i % 3 == 0 && i > 4)
		//	printf("║");
		//else
		printf("\t");
	}
    if (lrc == 0)
		printf("\033[38;5;46m╠══════\033[0m[%s]\n", ast->cmd);
	else if (lrc == 1)
		printf("\033[38;5;46m╔══════\033[0m[%s]\n", ast->cmd);
	else if (lrc == 2)
		printf("\033[38;5;46m╚══════\033[0m[%s]\n", ast->cmd);
    print_ast(ast->left, indent + 1, 2);
}

t_parser	*abstract_syntax_tree(t_init *init, t_parser **stack)
{
	t_parser	*ptr;
	t_parser	*new;

	new = NULL;
	ptr = lstlast_pars(*stack);
	if (ptr->type == XOR || ptr->type == XAND || ptr->type == PIPE)
	{
		new = lstnew_pars(ptr->cmd, ptr->type, ptr->prc);
		pop(stack);
		new->right = abstract_syntax_tree(init, stack);
		new->left = abstract_syntax_tree(init, stack);
		return (new);
	}
	else if (ptr)
	{
		new = lstnew_pars(ptr->cmd, ptr->type, ptr->prc);
		pop(stack);
		return (new);
	}
	return (new);
}

/* IDEA FOR AST CONSTRUCTION WAY [DOESN'T WORKING RIGHT NOW]
// Recursive function to construct the AST
ASTNode *constructAST(char **tokens, int *index) {
    char *token = tokens[*index];
    (*index)++;

    if (strcmp(token, "||") == 0 || strcmp(token, "&&") == 0 || strcmp(token, "|") == 0) {
        ASTNode *node = createNode(token);
        node->right = constructAST(tokens, index);
        node->left = constructAST(tokens, index);
        return node;
    } else {
        return createNode(token);
    }
}

// Function to print the AST in a tree-like format
void printAST(ASTNode *root, int indent) {
    if (root == NULL) {
        return;
    }
    printAST(root->right, indent + 4);
    for (int i = 0; i < indent; i++) {
        printf(" ");
    }
    printf("└── %s\n", root->cmd);
    printAST(root->left, indent + 4);
}*/