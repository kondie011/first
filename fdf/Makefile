# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knedzing <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/27 09:45:17 by knedzing          #+#    #+#              #
#    Updated: 2018/07/28 16:30:32 by knedzing         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = main.c \
	  put_pix.c \
	  handle_key_press.c \
	  get_next_line/get_next_line.c \
	  drawer.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

FLAGSMLX = -L/usr/local/include -lmlx -framework OpenGL -framework AppKit

LIBFT = -L./libft -lft

CC = gcc

INCLUDES = ./includes

LIBFT_PATH = ./libft

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -I$(INCLUDES)  $(FLAGSMLX) $(LIBFT)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
