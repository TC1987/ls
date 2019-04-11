NAME = ft_ls
BASE = src/main \
	   src/add \
	   src/display \
	   src/flags \
	   src/init \
	   src/parse \
	   src/long_format \
	   src/compare \
	   src/get_helpers \
	   src/bonus
SRC = $(addsuffix .c, $(BASE))
OBJ = $(addsuffix .o, $(BASE))
LIBFT = ./libft/libft.a
BPRINTF = ./b_printf/libftprintf.a
COMPILE = gcc -Wall -Wextra -Werror
COMPILE_SOFT = gcc
INCLUDE = -I. -I./libft/ -I./b_printf
RED = \x1b[31m
GREEN = \x1b[32m
RESET = \x1b[0m
SANITIZE = -fsanitize=address

all: $(NAME)

$(NAME): $(LIBFT) $(BPRINTF) $(SRC)
	@echo "$(GREEN)"compiling project"$(RESET)"
	@$(COMPILE) $(SRC) $(INCLUDE) $(LIBFT) -L ./libft $(BPRINTF) -L ./b_printf -o $(NAME) $(SANITIZE) -g
	@echo "$(GREEN)"project successfully compiled"$(RESET)"

$(LIBFT):
	@echo "$(GREEN)"compiling libft"$(RESET)"
	@make -C ./libft

$(BPRINTF):
	@echo "$(GREEN)"compiling printf"$(RESET)"
	@make -C ./b_printf

clean:
	@echo "$(RED)"cleaning files"$(RESET)"
	@make clean -C ./libft
	@make clean -C ./b_printf
	@/bin/rm -f $(OBJ)

fclean: clean
	@echo "$(RED)"cleaning library"$(RESET)"
	@make fclean -C ./libft
	@make fclean -C ./b_printf
	@echo "$(RED)"cleaning executable"$(RESET)"
	@/bin/rm -f $(NAME)

re: fclean all
