# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 08:55:18 by muzz              #+#    #+#              #
#    Updated: 2025/01/17 10:49:24 by muzz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
MINILIBX_DIR = ./minilibx-linux
GNL_DIR = ./get_next_line

# Source Files
SRC = so_long.c \
      load_texture.c \
      render_map.c \
      movement.c \
      libft.c \
      check_map.c \
      $(GNL_DIR)/get_next_line.c \
      $(GNL_DIR)/get_next_line_utils.c

# Object Files
OBJ = $(SRC:.c=.o)

# MiniLibX
MINILIBX = $(MINILIBX_DIR)/libmlx.a
MINILIBX_INC = -I $(MINILIBX_DIR)
MINILIBX_LNK = -L $(MINILIBX_DIR) -lmlx -lXext -lX11 -lm

# Cleanup
RM = rm -f

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(MINILIBX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MINILIBX_INC) $(MINILIBX_LNK)

# Compiling object files
%.o: %.c
	$(CC) $(CFLAGS) -I $(MINILIBX_DIR) -I $(GNL_DIR) -c $< -o $@

# Building MinilibX
$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

# Cleaning object files and MinilibX
clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C $(MINILIBX_DIR)

# Full clean, including the executable
fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(MINILIBX_DIR)

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re
