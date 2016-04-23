# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 14:09:58 by apachkof          #+#    #+#              #
#    Updated: 2016/04/23 17:21:22 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

CC=gcc

CFLAGS=-Wall -Wextra -Werror -O3

RM=rm -f

SRC=main.c\
	color.c\
	hooks.c\
	julia.c\
	mandelbrot.c\
	ship.c\
	util.c\

LIB= -framework OpenGL -framework AppKit libft/libft.a minilibx_macos/libmlx.a

INCL=-I libft/includes/ -I minilibx_macos/

OBJ=$(SRC:.c=.o)

$(NAME): $(NAME).h $(OBJ)
		make -C libft/
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCL) $(LIB)

%.o: %.c
		$(CC) $(CFLAGS) $(INCL) -c $< -o $@

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
