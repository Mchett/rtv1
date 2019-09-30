# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchett <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/19 18:05:38 by mchett            #+#    #+#              #
#    Updated: 2018/12/06 17:09:03 by mchett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCCOPT = -Wall -Wextra -Werror
SRC = ft*.c
NAME = libft.a

all: $(NAME)

$(NAME):
		gcc -c $(GCCOPT) $(SRC) 
		ar rc $(NAME) *.o
		
clean:
		rm -rf *.o

fclean: clean
		rm -rf $(NAME)

re: fclean all
