NAME = minishell
CC = cc 
FLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a
HEADER = includes/minishell.h libft/libft.h

SRC = parsing/create_list.c \
      parsing/expand.c \
      parsing/parsing.c \
      parsing/syntax.c \
      execute/error_handle.c \
      execute/execute_utilis.c \
      execute/execute.c \
      execute/find_path.c \
      execute/heredoc.c \
      execute/set_redirections.c \
      execute/utlis.c \
      execute/check_building.c \
      builtins/echo.c \
      builtins/env.c \
      builtins/pwd.c \
      builtins/cd.c \
      builtins/exit.c \
      builtins/export.c \
      builtins/utils.c \
      utils/append.c \
      utils/utils.c \
      utils/free_mem.c \
      utils/ft_strcmp.c \
      utils/ft_strjoin2.c \
      src/main.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(FLAGS) -lreadline $(OBJ) $(LIBFT_LIB) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Iincludes -c $< -o $@

clean:
	rm -rf $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re