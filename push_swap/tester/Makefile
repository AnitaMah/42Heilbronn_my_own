# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/03                               #+#    #+#              #
#    Updated: 2026/06/03                               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tester

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

SRC_DIR = src

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/generator.c \
	$(SRC_DIR)/shuffle.c \
	$(SRC_DIR)/runner.c \
	$(SRC_DIR)/checker.c \
	$(SRC_DIR)/valgrind.c \
	$(SRC_DIR)/statistics.c \
	$(SRC_DIR)/save_case.c \
	$(SRC_DIR)/utils.c

OBJ = $(SRC:.c=.o)

# path to push_swap (IMPORTANT FIX)
PUSH_SWAP = ../push_swap
CHECKER = ../checker_linux

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re