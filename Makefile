# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 08:55:18 by muzz              #+#    #+#              #
#    Updated: 2025/01/15 08:58:31 by muzz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = so_long.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./minilibx-linux
LIBFT = $(LIBFT_DIR)/libmlx.a

LIBFT_INC = -I $(LIBFT_DIR)
LIBFT_LNK = -L $(LIBFT_DIR) -lmlx -lXext -lX11 -lm

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_INC) $(LIBFT_LNK)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
