NAME = minishell

CC = gcc

CFLAGS =  -Wall -Wextra -Werror

INC  = mini_shell.h

SRC =	mini_shell.c \
		ft_split.c \
		ft_memcpy.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_substr.c \

SOFILES = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SOFILES) $(INC)
	$(CC)  $(CFLAGS) $(SOFILES) -lreadline -o $(NAME)

clean :
	@-rm -rf $(SOFILES)

fclean : clean
	@-rm -rf minishell

re : fclean all
