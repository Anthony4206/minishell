#ifndef CONTEXT_H
# define CONTEXT_H

# include "lexer/lexer.h"
# include "parser/tree.h"

typedef enum e_token_type
{
	TOK_REDIR = 1,
	TOK_STRING,
	TOK_AND,
	TOK_OR,
	TOK_PIPE,
	TOK_L_PARENTHESIS,
	TOK_R_PARENTHESIS,
	TOK_ADD,
	TOK_START,
	TOK_EOF
}	t_token_type;

typedef enum e_string_type
{
	STRING_UNQUOTED = 1,
	STRING_QUOTED,
	STRING_DQUOTED
} t_string_type;

typedef enum e_redir_type
{
	REDIR_INFILE = 1,
	REDIR_OUTFILE,
	REDIR_HERE_DOC,
	REDIR_APP_OUTFILE
} t_redir_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	t_string_type	string;
	t_redir_type	redir;
	struct s_token	*next;
}					t_token;

typedef struct s_ctx
{
	t_token		*start_lexer;
	t_ast_node	*exec_tree;
	char		**env;
	char		**fd_here_doc;
	int			len;
	int			is_first;
	int 		ex_status;
}				t_ctx;

typedef struct g_prompt
{
	int		prompt;
	pid_t	last_pid;
}	t_prompt;

#endif