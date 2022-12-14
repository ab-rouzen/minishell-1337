.PHONY: all re clean fclean

NAME = minishell
CC = gcc
M_INCL_DIR = src/include/
M_INCL_NAME = execution.h lexer.h parser.h quoting.h types.h
M_INCL_M = $(addprefix $(M_INCL_DIR), $(M_INCL_NAME))
M_SRC_PRIME_DIR = src/
M_SRC_PARSE_DIR = src/parse/
M_SRC_EXEC_DIR = src/execute/
FALGS = $(CPPFLAGS) -Wall -Wextra -Werror -g #-fsanitize=address
M_SRC_PARSE_NAME = lexer lexer_2 \
				lexer_redirection utils utils_parser utils_quotes \
				utils_tokenizer parser parser_pipe \
				parser_redirection quoting garbage_collector \
				utils_cmd_construct utils_environ \
				heredoc_expand
M_SRC_EXEC_NAME = execution_utils heredoc utils \
				execute redirection heredoc_utils signals \
				builtin_utils 1_builtin_utils 2_builtin_utils \
				3_builtin_utils 4_builtin_utils wait_child \
				heredoc_count_utils env_utils redirection_utils \
				5_ft_builtin_utils

M_SRC_PRIME_NAME = init main
M_INCLUDE_NAME = lexer minishell parser quoting execution types
L_READ_LINE = -lreadline 
BUILD_DIR = build/
M_SRC_DIR  = src/
LIBS = $(LIB_FT)libft.a
LIB_FT = lib/libft/
LIB_GNL = lib/get_next_line/
LFLAGS = -L/Users/${USER}/.brew/Cellar/readline/8.2.1/lib
IFLAGS = -I/Users/${USER}/.brew/Cellar/readline/8.2.1/include

# Header files
M_INCUDE = $(addsuffix .h, $(M_INCLUDE_NAME))
M_INCLUDE_PATH = $(addprefix $(M_INCL_DIR), $(M_INCLUDE))

# Source files
M_SRC_PRIME_PATH = $(addprefix $(M_SRC_PRIME_DIR), $(M_SRC_PRIME_NAME))
M_SRC_PARSE_PATH = $(addprefix $(M_SRC_PARSE_DIR), $(M_SRC_PARSE_NAME))
M_SRC_EXEC_PATH = $(addprefix $(M_SRC_EXEC_DIR), $(M_SRC_EXEC_NAME))
M_SRC_PATH = $(M_SRC_PARSE_PATH) $(M_SRC_PRIME_PATH) $(M_SRC_EXEC_PATH)
M_SRC_NAME = $(M_SRC_PARSE_NAME) $(M_SRC_PRIME_NAME) $(M_SRC_EXEC_NAME)
M_SRC = $(addsuffix .c, $(M_SRC_PATH))

# Object files
M_OBJ = $(M_SRC:%=$(BUILD_DIR)%.o)


all : $(NAME)
	@echo everything is in order...

$(NAME) : $(M_OBJ) $(M_INCL_M) 
	make bonus -C $(LIB_FT)
	$(CC) $(LDFLAGS) $(FALGS) $(LFLAGS)  $(M_OBJ) $(LIBS) -o $(NAME) -lreadline

$(BUILD_DIR)%.c.o : %.c $(M_INCL_M)
	@mkdir -p $(dir $@)
	$(CC) $(FALGS) $(IFLAGS) -c $< -o $@

clean : 
	@make clean -C $(LIB_FT)
	rm -rf $(BUILD_DIR)

fclean : clean
	@make fclean -C $(LIB_FT)
	rm -rf $(NAME)

re : fclean all
