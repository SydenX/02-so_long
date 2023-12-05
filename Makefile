# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 13:47:45 by jtollena          #+#    #+#              #
#    Updated: 2023/12/05 16:58:59 by jtollena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SOURCES = srcs/main.c \
			srcs/utils.c \
			srcs/map_checks/surrounded.c \
			srcs/map_checks/linesize.c

OBJECTS = $(SOURCES:.c=.o)
INCLUDES = includes
FLAGS = #-Wall -Wextra #-Werror
LINKS = -I libft -L libft \
    -I /usr/local/include -L /usr/local/lib \
    -l mlx -l ft -l ftprintf -framework OpenGL -framework Appkit

# Remember to implement your rules...

%.o: %.c
	gcc $(FLAGS) -Ilibft -Imlx -I $(INCLUDES) -c $< -o $@

$(NAME): $(OBJECTS) $(INCLUDES)
	gcc $(OBJECTS) -Llibft -Lmlx -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	rm $(OBJECTS)
#Ne pas oublier d'enlever la ligne au dessus "rm"

clean:
	rm $(OBJECTS)

fclean: clean
	rm $(NAME)

re: fclean $(NAME)

.PHONY: re fclean clean