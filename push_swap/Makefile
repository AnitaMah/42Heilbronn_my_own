NAME = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c \
	src/init_stack.c \
	src/parse_args.c \
	src/is_sorted.c \
	src/sort_stack.c \
	src/free_stack.c \
	stack_operations/push.c \
	stack_operations/reverse.c \
	stack_operations/rotate.c \
	stack_operations/swap.c \
	stack_sorting/chunk_sort.c \
	stack_sorting/radix_sort.c \
	stack_sorting/selections_sort_addaptation.c \
	stack_sorting/untils_sort/normalize_index.c \
	stack_sorting/untils_sort/quick_sort.c \
	stack_sorting/untils_sort/untils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
