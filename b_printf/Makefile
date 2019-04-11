# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcho <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/12 19:51:35 by tcho              #+#    #+#              #
#    Updated: 2019/04/11 05:59:41 by tcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
BASE = b_printf \
	   ft_is_space \
	   ft_ia \
	   ft_operation \
	   ft_pc \
	   ft_ps \
	   ft_uitoa
SRC = $(addsuffix .c, $(BASE))
OBJ = $(addsuffix .o, $(BASE))
CFLAGS = -Wextra -Werror -Wall -c

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) $(SRC) -I.
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
