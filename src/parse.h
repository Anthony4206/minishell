#ifndef PARSE_H
# define PARSE_H

# include "structs.h"
# include "tree.h"

typedef enum	 e_node
{
	NODE_INFILE_DIR = 1,
	NODE_OUTFILE_DIR,
	NODE_HEREDOC,
	NODE_APP_OUT_REDIR,
	NODE_OR,
	NODE_AND,
	NODE_PIPE,
	NODE_PARENTHESIS,
	NODE_DATA
}				t_node_type;

int	ft_parse(t_ctx *ctx, t_ast_node tree);

#endif
