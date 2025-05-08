NAME = minishell
CC = cc 
FLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h
HEADER = includes/minishell.h 
ALL_HEADERS = $(HEADER) $(LIBFT_HEADER)

SRC = parsing/create_list.c \
	parsing/creat_list_utlis.c \
	parsing/expand.c \
	parsing/parsing.c \
	parsing/syntax.c \
	parsing/shell_level.c \
	parsing/expand_utlis.c \
	parsing/expand_utlis_2.c \
	parsing/expand_utlis_3.c \
	execute/error_handle.c \
	execute/execute_utilis.c \
	execute/execute.c \
	execute/find_path.c \
	execute/heredoc.c \
	execute/heredoc_utlis0_1.c \
	execute/heredoc_dollars.c \
	execute/heredoc_utlis1_1.c \
	execute/set_redirections.c \
	execute/utlis1_0.c \
	execute/utlis1_1.c \
	execute/check_building.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/pwd.c \
	builtins/cd.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/utils.c \
	builtins/unset.c \
	builtins/cd_utlis.c \
	builtins/export_utlis.c \
	utils/append.c \
	utils/utils.c \
	utils/free_mem.c \
	utils/ft_strcmp.c \
	utils/ft_strjoin2.c \
	utils/signals.c \
	src/main.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB): force_libft
	make -C $(LIBFT_DIR)

force_libft:
	@true

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(FLAGS) -lreadline $(OBJ) $(LIBFT_LIB) -o $(NAME)

%.o: %.c $(ALL_HEADERS)
	$(CC) $(FLAGS) -Iincludes -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re force_libft