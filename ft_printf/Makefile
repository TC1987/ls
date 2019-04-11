# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcho <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 00:32:50 by tcho              #+#    #+#              #
#    Updated: 2019/04/11 00:32:54 by tcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra

NAME = libftprintf.a

SRCS =	ft_printf.c helper.c print_p_s_c.c get_flags.c \
		print_d_i.c print_o_u_x.c print_f.c ft_atoi.c \
		ft_isdigit.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strnew.c

OBJ = ${SRCS:.c=.o}

all: $(NAME)
$(NAME):
	gcc $(CFLAGS) -c -I. $(SRCS)
	ar rcs $(NAME) $(OBJ)
clean:
	/bin/rm -f $(OBJ)
fclean:clean
	/bin/rm -f $(NAME)
re: fclean all

