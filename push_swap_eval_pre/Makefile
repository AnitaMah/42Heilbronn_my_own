# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/15 14:59:16 by anmakhov          #+#    #+#              #
#    Updated: 2026/06/18 14:10:15 by anmakhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iheader_file -Ilibft

LIBFT = libft/libft.a

SRC = main/main.c \
	main/is_sorted.c \
	main/compute_disorder.c \
	main/normalize_index.c \
	main/stack_from_array.c \
	main/untils_main.c \
	\
	untils/untils_parsing.c \
	untils/new_pasring.c \
	untils/bring_to_top.c \
	untils/quick_sort.c \
	untils/restore_to_a.c \
	\
	stack_operations/push.c \
	stack_operations/reverse.c \
	stack_operations/rotate.c \
	stack_operations/swap.c \
	\
	stack_sorting/chunk_sort.c \
	stack_sorting/radix_sort.c \
	stack_sorting/selections_sort_addaptation.c \
	stack_sorting/sort_small.c \
	\
	parsing/parse_args.c \
	parsing/ft_atoi_ps.c \
	parsing/check_errors.c \
	\
	stack/stack_free.c \
	stack/stack_init.c \
	stack/stack_utils.c \
	\
	flags/bench.c \
	flags/parse_args_utils.c \
	flags/parse_flags.c \
	flags/strategy_apply.c \
	flags/count_only.c



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
