# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchett <mchett@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 16:02:40 by mchett            #+#    #+#              #
#    Updated: 2019/10/07 14:49:11 by mchett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = RTv1
FLAGS = -Wall -Wextra -Werror -I includes/ -g #-fsanitize=address
LIBFLAGS = -L./libs/libft -lft -L./libs/minilibx -lmlx -framework OpenGL -framework AppKit
FILES = ambient.c cam.c cone.c cylinder.c get_next_line.c image.c key.c light.c main.c mlx.c parser.c parser2.c plane.c ray.c sphere.c vectors.c vectors2.c
INCFILES = includes/rtv1.h
SRCS = $(addprefix src/, $(FILES))
OBJ = $(addprefix objectives/, $(FILES:.c=.o))


all: lib
	make startuem -j

startuem: $(NAME)

$(NAME):$(OBJ) $(INCFILES)
	gcc $(FLAGS) $(LIBFLAGS) -o $(NAME) $(OBJ)

objectives/%.o: src/%.c | objectives
	gcc $(FLAGS) -o $@ -c $^

re: fclean all

lib:
	make -C ./libs/libft -j
	make -C ./libs/minilibx -j

clean:
	rm -rf objectives/
	make clean -C ./libs/libft
	make clean -C ./libs/minilibx

fclean: clean
	make fclean -C ./libs/libft
	rm -rf $(NAME)

objectives:
	mkdir -p objectives