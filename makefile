.PHONY: all re clean fclean

NAME = minishell
CC = gcc
M_INCL_DIR = src/include/
M_SRC_PARSE_DIR = src/parse/
M_SRC_PRIME_DIR = src/
FALGS = $(CPPFLAGS) -Wall -Wextra -g ##-fsanitize=address
M_SRC_PARSE_NAME = lexer lexer_2 \
				lexer_redirection utils utils_parser utils_quotes \
				utils_tokenizer parser parser_pipe \
				parser_redirection quoting garbage_collector \
				utils_cmd_construct utils_environ
M_SRC_PRIME_NAME = main
M_INCLUDE_NAME = lexer minishell parser quoting
L_READ_LINE = -lreadline
BUILD_DIR = build/
M_SRC_DIR  = src/
LIBS = lib/libft/libft.a
LIB_FT = lib/libft/

# Header files
M_INCUDE = $(addsuffix .h, $(M_INCLUDE_NAME))
M_INCLUDE_PATH = $(addprefix $(M_INCL_DIR), $(M_INCLUDE))

# Source files
M_SRC_PRIME_PATH = $(addprefix $(M_SRC_PRIME_DIR), $(M_SRC_PRIME_NAME))
M_SRC_PARSE_PATH = $(addprefix $(M_SRC_PARSE_DIR), $(M_SRC_PARSE_NAME))
M_SRC_PATH = $(M_SRC_PARSE_PATH) $(M_SRC_PRIME_PATH)
M_SRC_NAME = $(M_SRC_PARSE_NAME) $(M_SRC_PRIME_NAME)
M_SRC = $(addsuffix .c, $(M_SRC_PATH))

# Object files
M_OBJ = $(M_SRC:%=$(BUILD_DIR)%.o)

all : $(NAME)
	@echo everything is in order...
	./minishell

$(NAME) : $(M_OBJ) $(M_INCL_PATH) 
	make bonus -C $(LIB_FT)
	$(CC) $(LDFLAGS) $(FALGS) $(L_READ_LINE) $(M_OBJ) $(LIBS) -o $(NAME)

$(BUILD_DIR)%.c.o : %.c $(M_INCL_PATH)
	@mkdir -p $(dir $@)
	$(CC) $(FALGS) -c $< -o $@

clean : 
	@make clean -C $(LIB_FT)
	rm -rf $(BUILD_DIR)

fclean : clean
	@make fclean -C $(LIB_FT)
	rm -rf $(NAME)

re : fclean all
