a.PHONY: all re clean fclean

NAME = minishell
CC = gcc
M_INCL_DIR = src/include/
M_SRC_PRIME_DIR = src/
M_SRC_PARSE_DIR = src/parse/
M_SRC_EXEC_DIR = src/execute/
FALGS = $(CPPFLAGS) -Wall -Wextra #-g -fsanitize=address
M_SRC_PARSE_NAME = lexer lexer_2 \
				lexer_redirection utils utils_parser utils_quotes \
				utils_tokenizer parser parser_pipe \
				parser_redirection quoting garbage_collector \
				utils_cmd_construct utils_environ
M_SRC_EXEC_NAME = execution_utils mini_shell heredoc utils \
				execute redirection heredoc_utils

M_SRC_PRIME_NAME = init main  #exec_main 
M_INCLUDE_NAME = lexer minishell parser quoting execution
L_READ_LINE = -lreadline 
BUILD_DIR = build/
M_SRC_DIR  = src/
LIBS = $(LIB_FT)libft.a $(LIB_GNL)libgnl.a $(LIB_PRINTF)libftprintf.a
LIB_FT = lib/libft/
LIB_GNL = lib/get_next_line/
LIB_PRINTF = lib/printf/
LFLAGS = -L/Users/${USER}/.brew/opt/readline/lib
IFLAGS = -I/Users/${USER}/.brew/opt/readline/include

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

LFLAGS = -L/Users/imittous/.brew/opt/readline/lib
IFLAGS = -I/Users/imittous/.brew/opt/readline/include

# Object files
M_OBJ = $(M_SRC:%=$(BUILD_DIR)%.o)


all : $(NAME)
	@echo everything is in order...

$(NAME) : $(M_OBJ) $(M_INCL_PATH) 
	make bonus -C $(LIB_FT)
	make bonus -C $(LIB_GNL)
	$(CC) $(LDFLAGS) $(FALGS) $(LFLAGS) $(L_READ_LINE) $(M_OBJ) $(LIBS) -o $(NAME)

$(BUILD_DIR)%.c.o : %.c $(M_INCL_PATH)
	@mkdir -p $(dir $@)
	$(CC) $(FALGS) -c $< -o $@

clean : 
	@make clean -C $(LIB_FT)
	@make clean -C $(LIB_GNL)
	@make clean -C $(LIB_PRINTF)
	rm -rf $(BUILD_DIR)

fclean : clean
	@make fclean -C $(LIB_FT)
	@make fclean -C $(LIB_GNL)
	@make fclean -C $(LIB_PRINTF)
	rm -rf $(NAME)
a : all

re : fclean all
