/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:10:07 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/08 16:10:09 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void print_escaped(const char *str)
{
    if (!str) return;
    while (*str)
	{
        switch (*str)
		{
            case '\n': printf("\\n"); break;
            case '\"': printf("\\\""); break;
            case '\\': printf("\\\\"); break;
            default: putchar(*str);
        }
        str++;
    }
}

void print_ast_dot(t_bin_node *node)
{
    if (node == NULL) return;

    printf("\"%p\" [Content=\"", (void*)node);
    switch (node->type)
	{
        case TOKEN_WORD: printf("CMD: "); break;
        case TOKEN_REDIR_IN:
        case TOKEN_REDIR_OUT:
        case TOKEN_REDIR_APPEND:
        case TOKEN_REDIR_HEREDOC: printf("REDIR: "); break;
        case TOKEN_PIPE: printf("|"); break;
        default: printf("UNKNOWN"); break;
    }
    // Print all arguments for the node
    if (node->args)
	{
        for (int i = 0; node->args[i] != NULL; i++)
		{
            if (i > 0) printf(" "); // Add space between arguments
            print_escaped(node->args[i]);
        }
    }
    printf("\"];\n");
    if (node->left != NULL)
	{
        printf("\"%p\" -> \"%p\" [Node=\"L\"];\n", (void*)node, (void*)node->left);
        print_ast_dot(node->left);
    }
    if (node->right != NULL)
	{
        printf("\"%p\" -> \"%p\" [Node=\"R\"];\n", (void*)node, (void*)node->right);
        print_ast_dot(node->right);
    }
}

void generate_ast_diagram(t_bin_node *root)
{
    printf("Binary Tree Graph\n{\n");
    print_ast_dot(root);
    printf("}\n");
}

t_token    *validate_input_and_tokenize(char *input)
{
    char    *trimmed_input;
    t_token *tokens;
    
    trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
    free(input);
    if (trimmed_input == NULL)
        return (NULL);
    if (error_checker(trimmed_input))
    {
        free(trimmed_input);
        return (NULL);   
    }
    tokens = tokenize_input(trimmed_input);
    return (tokens);
}

void    print_binary_tree(t_bin_node *root, int level)
{
    level++;

    if (root == NULL)
        return ;
    printf("level %d : %d\n", level, root->type);
    if (root->left != NULL)
        print_binary_tree(root->left, level);
    if (root->right != NULL)
        print_binary_tree(root->right, level);
}

int	main(int argc, char **argv, char **env)
{
	char	    *input;
	t_token	    *tokens;
    t_bin_node  *ast;
	char	*cwd;

	if (argc > 0 && argv)
	{
		//cmd_signals(0);
		init_env(env);
		tokens = NULL;
		cwd = new_prompt();
		input = readline(cwd);
		while (input != NULL)
		{
            tokens = validate_input_and_tokenize(input);
            if (tokens == NULL)
            {
                printf("Tokenization Failed\n");
                return (1);
            }
            display_tokens(tokens);
            ast = parser(&tokens);
            print_binary_tree(ast, -1);
            generate_ast_diagram(ast);
			//main_exec(&input, &tokens);
			//ft_free(input);
			//ft_free(cwd);
			cwd = new_prompt();
			//cmd_signals(0);
			input = readline(cwd);
		}
		free_env(g_env);
	}
}
