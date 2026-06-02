NAME = tester

SRC = src/main.c \
      src/generator.c \
      src/shuffle.c \
      src/runner.c \
      src/checker.c \
      src/valgrind.c \
      src/statistics.c \
      src/save_case.c \
      src/utils.c \
	  stack_operations/push.c \
	  stack_operations/reverse.c \
	  stack_operations/rotate.c \
	  stack_operations/swap.c \
	  stack_sorting/chunk_sort.c \
	  stack_sorting/selections_sort_addaptation.c \
	  stack_sorting/radix_sort.c \
	  stack_sorting/untils_sort/normalize_index.c \
	  stack_sorting/untils_sort/quick_sort.c \
	  stack_sorting/untils_sort/untils.c

all:
	gcc $(SRC) -I include -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
