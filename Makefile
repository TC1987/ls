NAME = ls
BASE = main \
	   src/add \
	   src/display \
	   src/flags \
	   src/init \
	   src/parse \
	   src/long_format \
	   src/compare \
	   src/get_helpers
SRC = $(addsuffix .c, $(BASE))
OBJ = $(addsuffix .o, $(BASE))
LIBFT = ./libft/libft.a
PRINTF = ./ft_printf/libftprintf.a
COMPILE = gcc -Wall -Wextra -Werror
COMPILE_SOFT = gcc
INCLUDE = -I. -I./libft/ -I./ft_printf
RED = \x1b[31m
GREEN = \x1b[32m
RESET = \x1b[0m
SANITIZE = -fsanitize=address

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(SRC)
	@echo "$(GREEN)"Compiling Project"$(RESET)"
	@$(COMPILE) $(SRC) $(INCLUDE) $(LIBFT) -L ./libft $(PRINTF) -L ./ft_printf $(SANITIZE) -g
	@echo "$(GREEN)"Project Successfully Compiled"$(RESET)"

$(LIBFT):
	@echo "$(GREEN)"Compiling Libft"$(RESET)"
	@make -C ./libft

$(PRINTF):
	@echo "$(GREEN)"Compiling Printf"$(RESET)"
	@make -C ./ft_printf

clean:
	@echo "$(RED)"Cleaning Files"$(RESET)"
	@make clean -C ./libft
	@/bin/rm -f $(OBJ)

fclean: clean
	@echo "$(RED)"Cleaning Library"$(RESET)"
	@make fclean -C ./libft
	@echo "$(RED)"Cleaning Executable"$(RESET)"
	@/bin/rm -f $(NAME)

re: fclean all
