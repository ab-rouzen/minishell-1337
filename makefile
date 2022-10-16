.PHONY: all re clean fclean

NAME = minishell
CC = gcc
M_INCL = ./src/minishell.h
FALGS = $(CPPFLAGS) -Wall -Wextra -g 
M_SRC_NAME = main
L_READ_LINE = -lreadline
BUILD_DIR = build/
M_SRC_DIR  = src/
LIBS = lib/libft/libft.a
LIB_FT = lib/libft/
M_SRC = $(addsuffix .c, $(M_SRC_NAME))
M_SRC_P = $(addprefix $(M_SRC_DIR), $(M_SRC))
M_OBJ = $(addsuffix .o, $(M_SRC_NAME))
M_OBJ_P = $(addprefix $(BUILD_DIR), $(M_OBJ))

all : $(NAME)
	@echo everything is in order...

$(NAME) : $(M_OBJ_P) $(M_INCL) 
	$(CC) $(LDFLAGS) $(FALGS) $(L_READ_LINE) $(M_OBJ_P) $(LIBS) -o $(NAME)

$(BUILD_DIR)%.o : $(M_SRC_DIR)%.c $(M_INCL)
	@make -C $(LIB_FT)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FALGS) -c $< -o $@

clean : 
	@make clean -C $(LIB_FT)
	rm -rf $(BUILD_DIR)

fclean : clean
	@make fclean -C $(LIB_FT)
	rm -rf $(NAME)

re : fclean all
