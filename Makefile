# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 15:19:30 by muzz              #+#    #+#              #
#    Updated: 2025/01/22 15:47:37 by muzz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

GNL_DIR = get_next_line
MLX_DIR = minilibx-linux

SRC = so_long.c \
	  check_map.c \
	  check_map2.c \
	  error_free.c \
	  get_map_data.c \
	  libft_sl.c \
	  mechanism.c \
	  get_next_line.c \
	  get_next_line_utils.c

OBJ = $(SRC:.c=.o)

MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) -lX11 -lXext -lm

$(MLX):
	make -C $(MLX_DIR)

%.o : %.c
	$(CC) $(CFLAGS) -I $(MLX_DIR) -I $(GNL_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
