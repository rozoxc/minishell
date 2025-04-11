NAME = minishell
CC = cc 
FLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
HEADER = includes/minishell.h libft/libft.h
SRC = parsing/expander.c \
      parsing/lexer.c \
      parsing/parsing.c \
      parsing/redirect.c \
      parsing/main_parser.c \
      execute/error_handle.c \
      execute/execute_utilis.c \
      execute/execute.c \
      execute/find_path.c \
      src/main.c \
∆∆ OBJ = $(SRC:.c=.o)
all	:	$(NAME) $(LIBFT_LIB)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(NAME)	:	$(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_LIB) -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	make clean -C $(LIBFT_DIR)
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re:	fclean all
.PHONY: clean