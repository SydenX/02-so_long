# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 13:47:45 by jtollena          #+#    #+#              #
#    Updated: 2023/12/11 12:41:58 by jtollena         ###   ########.fr        #
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
			srcs/map_checks/map_init.c \
			srcs/node_manager/node_1.c \
			srcs/node_manager/node_utils.c \
			srcs/image_manager/image_1.c \
			srcs/error_manager/error_1.c

OBJECTS = $(SOURCES:.c=.o)
INCLUDES = includes
FLAGS =  -Wall -Wextra #-Werror
LINKS = -I libft -L libft \
    -I /usr/local/include -L /usr/local/lib \
    -l mlx -l ft -l ftprintf -framework OpenGL -framework Appkit

%.o: %.c
	gcc $(FLAGS) -Ilibft -Imlx -I $(INCLUDES) -c $< -o $@

$(NAME): $(OBJECTS) $(INCLUDES)
	gcc $(OBJECTS) -Llibft -Lmlx -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm $(OBJECTS)

fclean: clean
	rm $(NAME)

re: fclean $(NAME)

.PHONY: re fclean clean