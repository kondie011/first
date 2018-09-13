# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knedzing <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/23 15:30:51 by knedzing          #+#    #+#              #
#    Updated: 2018/09/03 18:38:22 by knedzing         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -c

HEADER = -I.

SOURCE = *.c

OBJECTS = $(SOURCE:.c=.o)

LFLAGS = ar rc

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCE) $(HEADER)
	$(LFLAGS) $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJECTS)

fclean:
	/bin/rm -f $(OBJECTS)
	/bin/rm -f $(NAME)

re: fclean all
