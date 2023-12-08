# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jetol <jetol@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 13:47:45 by jtollena          #+#    #+#              #
#    Updated: 2023/12/08 12:33:07 by jetol            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SOURCES = srcs/main.c \
			srcs/utils.c \
			srcs/map_checks/surrounded.c \
			srcs/map_checks/linesize.c \
			srcs/map_checks/nodestype.c \
			srcs/map_checks/get_sizes.c \
			srcs/map_checks/pathfinder.c \
			srcs/node_manager/node_1.c \
			srcs/node_manager/node_utils.c \
			srcs/image_manager/image_1.c \
			srcs/error_manager/error_1.c

OBJECTS = $(SOURCES:.c=.o)
INCLUDES = includes
FLAGS =  #-fsanitize=address#-Wall -Wextra #-Werror
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