#include <string.h>
#include <errno.h>

#include "libft.h"
#include "close.h"
#include "tree.h"

/**
 *
	<commamd parenthesis> ::=   '(' <command line> ')'  '||'    <list>
                        	|   '(' <command line> ')'  '&&'    <list>
                        	|   '(' <command line> ')'  '<'     <list>
                        	|   '(' <command line> ')'  '>'     <list>
                        	|   '(' <command line> ')'  '>>'    <list>
                        	|   '(' <command line> ')'  '<<'    <list>
                        	|   '(' <command line> ')'  '|'     <list>
                        	|   '(' <command line> ')'
                        	|   <command line>
    
    <command line>	::= 	<job> '||' <command line>
						| 	<job> '&&' <command line>
						|	<job>

	<job>			::=		<command>   '|'     <job>
						|	<command>   '||'    <job>
						|	<command>   '&&'    <job>’
						|	<command>

	<command>		::=		<simple command> '<' <filename>
						|	<simple command> '>' <filename>
						|	<simple command> '>>' <filename>
						|	<simple command> '<<' <EOF>
						|	<simple command>

	<simple command>::=		<pathname> <token list>

	<token list>	::=		<token> <token list>
						|	(EMPTY)
 *
**/

t_tree	*ast_cmd_parenth(t_token *lexer)
{
	t_tree	*ret;

	ret = malloc(sizeof(t_tree));
	while(lexer)
	{
		
	}


}

int	ft_parse(t_ctx *ctx, t_tree *tree)
{
	if (!ctx->start_lexer)
		return (ft_return_err("empty lexer", strerror(errno)));
	tree = ast_cmd_parenth(ctx->start_lexer);
	return (1);
}
