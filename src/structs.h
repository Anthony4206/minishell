#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>

typedef	enum e_token_type
{
	TOK_INFILE_REDIR = 1,
	TOK_OUTFILE_REDIR,
	TOK_HERE_DOC,
	TOK_APP_OUT_REDIR,
	TOK_STRING,
	TOK_AND,
	TOK_OR,
	TOK_PIPE,
	TOK_L_PARENTHESIS,
	TOK_R_PARENTHESIS
}	t_token_type;

typedef enum e_string_type
{
	STRING_UNQUOTED = 1,
	STRING_QUOTED,
	STRING_DQUOTED
}	t_string_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	t_string_type	string;
	struct s_token	*next;
}					t_token;

typedef struct s_ctx
{
	t_token	*start_lexer;
	char	**env;
}			t_ctx;

#endif
