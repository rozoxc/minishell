NAME = minishell
CC = cc 
FLAGS = -Wall -Werror -Wextra
LIB = includes/minishell.h
SRC = parsing/expander.c \
	  parsing/lexer.c \
	  parsing/parsing.c \
	  parsing/redirect.c \
	  utils/ft_split.c \
	  utils/ft_strcmp.c \
	  utils/ft_strlen.c\

OBJ = $(SRC:.c=.o)

all :$(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)

.PHONY: clean