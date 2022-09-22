#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "parse.h"
#include "libft.h"
#include "close.h"
#include "tree.h"

/**
 *
	<commamd parenthesis> ::=   '(' <command line> ')'  '||'    <command parenthesis>
                        	|   '(' <command line> ')'  '&&'    <command parenthesis>
                        	|   '(' <command line> ')'  '|'		<command parenthesis>
                        	|   '(' <command line> ')'  <command parenthesis>
                        	|   '(' <command line> ')'
							|   <command line>
    
    <command line>	::= 	<job> <command line>
						|	<job>

	<job>			::=		<command>   '|'     <job>
						|	<command>   '||'    <job>
						|	<command>   '&&'    <job>
						|	<command>   '|'
						|	<command>   '||'
						|	<command>   '&&'
						|	<command>

	<command>		::=		<simple command> '<' <filename>
						|	'<' <filename>
						|	<simple command> '>' <filename>
						|	'>' <filename>
						|	<simple command> '>>' <filename>
						|	'>>' <filename>
						|	<simple command> '<<' <EOF>
						|	'<<' <EOF>
						|	<simple command>

	<simple command>::=		<pathname> <token list>

	<token list>	::=		<token> <token list>
						|	(EMPTY)
 *
**/

void	ft_show_tree(t_tree *tree)
{
	t_ast_node	*ptr;
	t_ast_node *cpy;
	int i;

	i = 1;
	cpy = tree->root;
	while (cpy)
	{
		printf("type : %d | %d	", cpy->type, i);
		if (cpy->node_content)
			printf("%s\n", cpy->node_content);
		else
			printf("\n");
		if (cpy->left)
		{
			ptr = cpy;
			cpy = cpy->left;
			printf("type[L] : %d	", cpy->type);
			if (cpy->node_content)
				printf("%s\n", cpy->node_content);
			else
			{
				printf("\n");
				cpy = ptr->right;
			}
			i++;
		}
		else if (cpy->right)
		{
			cpy = cpy->right;
			i++;
		}
		else
			return ;
	}
}

t_tree	*ast_cmd_parenth(t_token *lexer)
{
	t_tree	*ret;

	ret = malloc(sizeof(t_tree));
	ret->root = NULL;
	while(lexer)
	{
		ast_add_node(ret, lexer->content, lexer->type);
		lexer = lexer->next;
	}
	ft_show_tree(ret);
	return (ret);
}

int	ft_parse(t_ctx *ctx, t_tree *tree)
{
	if (!ctx->start_lexer)
		return (ft_return_err("empty lexer", strerror(errno)));
	tree = ast_cmd_parenth(ctx->start_lexer);
	return (1);
}
