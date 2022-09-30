NAME			= minishell

SRC				= src/main.c src/lexer.c src/lexer_utils.c src/token_list.c \
					src/close.c src/tree_utils.c src/ast_destroy.c \
					src/parse.c src/parenthesis.c src/echo.c src/pwd.c \
					src/env.c src/cd.c src/export.c

SRC_B			= 

OBJ				= ${SRC:.c=.o}
OBJ_B			= ${SRC_B:.c=.o}

INCLUDE 		= -I./include/ 

RL              = -L/Users/${USER}/.brew/opt/readline/lib -lreadline #-L/usr/local/Cellar/readline/8.1.2/lib -lreadline

HEAD			= include/libft.h

LIBS 			= ./libft/
				
CC 				= gcc -g
CFLAGS 			= -Wall -Wextra -Werror -fsanitize=address

AR 				= ar rcs
RM 				= rm -f

GREEN			:= "\033[0;32m"
CYAN			:= "\033[0;36m"
RESET			:= "\033[0m"

%.o:			%.c
				@${CC} ${CFLAGS} ${INCLUDE} -o $@ -c $<

all: 			${NAME}

bonus:			${OBJ_B} ${HEAD}
				@make all -C ${LIBS}
				@echo ${GREEN}"Successfully updated 'libft'" ${RESET}
				@${CC} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJ_B} ${LIBS}libft.a
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}
				@touch bonus

${NAME}:		${OBJ} ${HEAD}
				@make all -C ${LIBS}
				@echo ${GREEN}"Successfully updated 'libft'" ${RESET}
				@${CC} ${RL} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJ} ${LIBS}libft.a
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}

clean:
				@make clean -C ${LIBS}
				@${RM} ${OBJ} ${OBJ_B}
				@echo ${CYAN}"Cleaned '${NAME}' objects with success"${RESET}
				
fclean:			clean
				@make fclean -C ${LIBS}
				@${RM} ${NAME} ${NAME_B}
				@echo ${CYAN}"Removed '${NAME}' with success"${RESET}

re:				fclean all

.PHONY: 		all clean fclean re
