# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchett <mchett@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 16:02:40 by mchett            #+#    #+#              #
#    Updated: 2019/09/30 17:32:00 by mchett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rtv1
FLAGS = -Wall -Wextra -Werror -I includes/ -g
LIBFLAGS = -L./libs/libft -lft -L./libs/minilibx -lmlx -framework OpenGL -framework AppKit
FILES = image.c mlx.c render.c vectors.c main.c sphere.c
INCFILES = includes/rtv1.h
SRCS = $(addprefix src/, $(FILES))
OBJ = $(addprefix objectives/, $(FILES:.c=.o))


all: $(NAME)

$(NAME):$(OBJ) $(INCFILES) | lib
	gcc $(FLAGS) $(LIBFLAGS) -o $(NAME) $(OBJ)

objectives/%.o: src/%.c | objectives
	gcc $(FLAGS) -o $@ -c $^

re: fclean all

lib:
	make -C ./libs/libft
	make -C ./libs/minilibx

clean:
	rm -rf objectives/
	make clean -C ./libs/libft
	make clean -C ./libs/minilibx

fclean: clean
	make fclean -C ./libs/libft
	rm -rf $(NAME)

objectives:
	mkdir -p objectives